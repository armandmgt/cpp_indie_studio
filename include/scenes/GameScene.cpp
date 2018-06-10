/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** gamescene
*/

#include "engine/systems/PlayerRotationSystem.hpp"
#include "engine/systems/ExplosionSystem.hpp"
#include "engine/systems/DespawnSystem.hpp"
#include "engine/systems/BreakDestructibleSystem.hpp"
#include "engine/systems/PlayerMovement.hpp"
#include "engine/systems/MovementSystem.hpp"
#include "engine/systems/ParseInputSystem.hpp"
#include "engine/systems/PutBombSystem.hpp"
#include "engine/Components.hpp"
#include "GameScene.hpp"

ids::GameScene::GameScene(std::shared_ptr<gfx::Renderer> r) : _world{std::make_shared<ecs::World>(r)},
	_renderer{r}, _event{r->getEventReceiver()}, _ai1{0LU, _world, {21, 19}}, _ai2{3LU, _world, {21, 19}} {
	Map map(21, 19);

	map.initMap(20);
	map.printMap();
	_world->createGround(21, 19, "../assets/meshs/ground.obj");
	_world->spawnEntitiesFromMap(std::move(map.getMap()));
	_renderer->addSkybox("../assets/skybox/hell");
	_initSystem();
	_renderer->setCameraFPS();
	_world->drawEntities();
}

ids::GameScene::~GameScene() noexcept
{
	_renderer->clearScene();
}

void ids::GameScene::_initSystem()
{
	_systemList.emplace_back(
		new ecs::ParseInput(_world->getEntities(), _renderer->getEventReceiver(), _ai1, _ai2));
	_systemList.emplace_back(new ecs::PlayerMovement(_world->getEntities()));
	_systemList.emplace_back(new ecs::PlayerRotationSystem(_world->getEntities(), _renderer));
	_systemList.emplace_back(new ecs::MovementSystem(_world->getEntities(), _renderer));
	_systemList.emplace_back(new ecs::PutBombSystem(_world->getEntities(), _world));
	_systemList.emplace_back(new ecs::ExplosionSystem(_world->getEntities(), _renderer, _world));
	_systemList.emplace_back(new ecs::DespawnSystem(_world->getEntities(), _renderer, _world));
	_systemList.emplace_back(new ecs::BreakDestructibleSystem(_world->getEntities(), _renderer, _world));
}

bool ids::GameScene::_isWin()
{
	std::size_t countPlayer = 0;
	for (auto &entity : *_world->getEntities()) {
		if (entity->hasComponent<ecs::Character>()) {
			countPlayer++;
		}
	}
	return !(countPlayer == 1 || countPlayer == 0);
}

ids::IScene::sceneId ids::GameScene::run() {
	while (_renderer->isRunning() && !_event.isKeyDown(irr::KEY_ESCAPE)) {
		if (!_isWin()) {
			_renderer->clearScene();
			return MENU;
		}
		_renderer->render();
		_event.hasEvent();
		for (auto &it : _systemList) {
			it->update(1);
		}
	}
	if (!_renderer->isRunning())
		return ids::IScene::QUIT;
	return PAUSE;
}
