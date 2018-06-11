/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PlayerMovement
*/

#include <memory>
#include "engine/systems/PutBombSystem.hpp"

namespace ecs {
	PutBombSystem::PutBombSystem(entityVector allEntities, std::shared_ptr<ecs::World> world)
		: System(allEntities), _world(world)
	{
	}

	void PutBombSystem::update(double delta[[maybe_unused]]) {
		auto players = getEntities(COMP_CHARACTER, COMP_INPUT, COMP_POSITION);
		auto bombs = getEntities(COMP_EXPLOSION, COMP_POSITION);

		for (auto player : players) {
			auto &input = player->getComponent<Input>();
			auto &stats = player->getComponent<Character>();
			auto &playerPos = player->getComponent<Position>();
			auto bombsInMap = std::count_if(bombs.begin(), bombs.end(), [player](Entity *bomb) {
				return player->id == bomb->getComponent<Explosion>().ownerId;
			});
			if (input.putBomb && bombsInMap < stats.maxBombs && _isValidPosition(playerPos, bombs))
				_world->spawnBombSystem(player);
			input.putBomb = false;
		}
	}

	bool PutBombSystem::_isValidPosition(Position &position, std::vector<Entity *> bombs)
	{
		for (auto bomb : bombs) {
			auto &posBomb = bomb->getComponent<Position>();
			auto posRounded = roundPos<int>(posBomb.x, posBomb.y);
			auto roundedPos = roundPos<int>(position.x, position.y);
			if (roundedPos.x == posRounded.x && roundedPos.y == posRounded.y)
				return false;
		}
		return true;
	}
}