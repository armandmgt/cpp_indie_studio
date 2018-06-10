/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PlayerAI
*/

#include <chrono>
#include <functional>
#include "PlayerAI.hpp"

namespace {
	template<class T>
	vec2d<T> toIntegerPos(const vec2d<float> &pos) {
		return {static_cast<T>(std::lround(pos.x)),
			static_cast<T>(std::lround(pos.y))};
	}

	template<class T>
	vec2d<T> toIntegerPos(float x, float y) {
		return {static_cast<T>(std::lround(x)),
			static_cast<T>(std::lround(y))};
	}

	bool aligned(float x1, float x2, float gridSize) {
		return std::abs(x1 - x2) < gridSize;
	}

	bool inRange(float x, float origin, float radius) {
		return std::abs(x - origin) < radius;
	}

	template<class T>
	void clear(T &container) {
		T newContainer;
		std::swap(container, newContainer);
	}

	void goDirection(vec2d<float> &pos, evt::eventAction direction) {
		static const std::map<evt::eventAction, vec2d<float>> moves{
			{evt::MOVEUP, {0.f, 1.f}}, {evt::MOVEDOWN, {0.f, -1.f}},
			{evt::MOVELEFT, {-1.f, 0.f}}, {evt::MOVERIGHT, {1.f, 0.f}},
		};
		pos += moves.at(direction);
	}
}

ids::PlayerAI::PlayerAI(size_t _id, std::shared_ptr<ecs::World> _world, vec2d<std::size_t> _mapSize)
	: _id{_id}, _world{_world}, _allEntities{}, _players{}, _bombs{},
	_map{_mapSize.x, std::vector<cellType>{_mapSize.y}}, _road{},
	_directions{evt::MOVEUP, evt::MOVEDOWN, evt::MOVELEFT, evt::MOVERIGHT}
{
}

evt::Event ids::PlayerAI::computeAction()
{
//	auto start = std::chrono::steady_clock::now();
	_updateMap();
//	_printMap();

	if (_myself == nullptr)
		return {evt::MOVEMENT, evt::NOTHING, evt::NONE};
	const auto &positionComponent = _myself->getComponent<ecs::Position>();
	vec2d<float> pos{positionComponent.x, positionComponent.y};
	if (_willDie(pos)) {
		evt::eventAction action = _findSafePlace(pos);
		return {evt::MOVEMENT, action, evt::NONE};
	}
	return {evt::MOVEMENT, evt::NOTHING, evt::NONE};
}

void ids::PlayerAI::_updateMap()
{
	_allEntities.clear();
	_players.clear();
	_bombs.clear();
	std::transform(_world->entities->begin(), _world->entities->end(), std::back_inserter(_allEntities),
		[](auto &e) { return e.get(); });
	auto it = std::find_if(_allEntities.begin(), _allEntities.end(), [this](ecs::Entity *e) {
		return e->hasComponent<ecs::Character>() && e->getComponent<ecs::Character>().id == _id;
	});
	if (it == _allEntities.end()) {
		_myself = nullptr;
		return;
	}
	_myself = *it;
	std::copy_if(_allEntities.begin(), _allEntities.end(), std::back_inserter(_players),
		[](const ecs::Entity *e) { return e->hasComponent<ecs::Character>(); });
	std::copy_if(_allEntities.begin(), _allEntities.end(), std::back_inserter(_bombs),
		[](const ecs::Entity *e) { return e->hasComponent<ecs::Explosion>(); });
	_constructTypesMap();
}

void ids::PlayerAI::_constructTypesMap()
{
	std::for_each(_map.begin(), _map.end(), [this](std::vector<cellType> &row) {
		std::fill(row.begin(), row.end(), EMPTY);
	});
	std::for_each(_allEntities.begin(), _allEntities.end(), [this](const ecs::Entity *entity) {
		_findCellType(entity);
	});
	std::for_each(_bombs.begin(), _bombs.end(), [this](const ecs::Entity *bomb) {
		const auto &bombPosComponent = bomb->getComponent<ecs::Position>();
		vec2d<std::size_t> integerPos = toIntegerPos<std::size_t>(bombPosComponent.x, bombPosComponent.y);
		_map.at(integerPos.x).at(integerPos.y) = BOMB;
	});
}

void ids::PlayerAI::_findCellType(const ecs::Entity *entity)
{
	if (!entity->hasComponent<ecs::Position>())
		return;
	const ecs::Position &pos = entity->getComponent<ecs::Position>();
	if (entity->hasComponent<ecs::Destructible>() && !entity->hasComponent<ecs::Character>()) {
		vec2d<std::size_t> integerPos = toIntegerPos<std::size_t>(pos.x, pos.y);
		_map.at(integerPos.x).at(integerPos.y) = BOX;
	} else if (!entity->hasComponent<ecs::Destructible>() && !entity->hasComponent<ecs::Orientation>()) {
		vec2d<std::size_t> integerPos = toIntegerPos<std::size_t>(pos.x, pos.y);
		_map.at(integerPos.x).at(integerPos.y) = WALL;
	}
}

bool ids::PlayerAI::_willDie(const vec2d<float> &pos)
{
	auto bombIt = std::find_if(_bombs.begin(), _bombs.end(), [&pos](const ecs::Entity *bomb) {
		const auto &bombPosComponent = bomb->getComponent<ecs::Position>();
		const auto &bombExplComponent = bomb->getComponent<ecs::Explosion>();
		return (aligned(pos.x, bombPosComponent.x, 0.5) &&
			inRange(pos.x, bombPosComponent.x, bombExplComponent.power)) ||
			(aligned(pos.y, bombPosComponent.y, 0.5) &&
			inRange(pos.y, bombPosComponent.y, bombExplComponent.power));
	});
	return bombIt != _bombs.end();
}

evt::eventAction ids::PlayerAI::_findSafePlace(vec2d<float> &pos)
{
	if (!_road.empty() && _isSafeRoad(_road)) {
		auto direction = _road.back();
		_road.pop_back();
		return direction;
	}
	clear(_road);

	std::unique_ptr<PathTree> pathsLengths = std::make_unique<PathTree>(evt::NOTHING, 0);
	std::list<vec2d<float>> visited;
	_findSaferCell(pos, pathsLengths, visited);
	auto &bestPath = *std::min_element(pathsLengths->leafs.begin(), pathsLengths->leafs.end(),
		[](const auto &p1, const auto &p2) {
			return (p1 && p2 && p1->length < p2->length) || !p2;
		});
	while (bestPath && bestPath->length) {
		_road.push_front(bestPath->path);
		bestPath = std::move(*std::min_element(pathsLengths->leafs.begin(), pathsLengths->leafs.end(),
			[](const auto &p1, const auto &p2) {
				return (p1 && p2 && p1->length < p2->length) || p2;
			}));
	}
	return _road.front();
}

bool ids::PlayerAI::_isSafeRoad(std::list<evt::eventAction> road)
{
	const auto &posComponent = _myself->getComponent<ecs::Position>();
	vec2d<float> currentPos = {posComponent.x, posComponent.y};

	while (!road.empty()) {
		auto path = road.back();
		goDirection(currentPos, path);
		if (_willDie(currentPos)) {
			return false;
		}
		road.pop_back();
	}
	return true;
}

void ids::PlayerAI::_findSaferCell(vec2d<float> &pos, std::unique_ptr<PathTree> &pathsLengths,
	std::list<vec2d<float>> &visited)
{
	if (!_willDie(pos))
		return;
	std::for_each(_directions.begin(), _directions.end(), [&](evt::eventAction dir) {
		auto copyPos = pos;
		goDirection(copyPos, dir);
		auto integerPos = toIntegerPos<std::size_t>(copyPos);
		if (_map.at(integerPos.x).at(integerPos.y) != EMPTY ||
			std::find(visited.begin(), visited.end(), pos) != visited.end()) {
			return;
		}
		visited.push_back(copyPos);
		pathsLengths->leafs[dir - 1] = std::make_unique<PathTree>(dir, pathsLengths->length + 1);
		_findSaferCell(copyPos, pathsLengths->leafs[dir - 1], visited);
	});
}
