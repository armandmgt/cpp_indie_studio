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
		auto entities = getEntities(COMP_CHARACTER, COMP_INPUT);
		auto bombs = getEntities(COMP_EXPLOSION);

		for (auto player : entities) {
			auto &input = player->getComponent<Input>();
			auto &stats = player->getComponent<Character>();
			auto bombsInMap = std::count_if(bombs.begin(), bombs.end(), [player](Entity *bomb) {
				return player->id == bomb->getComponent<Explosion>().ownerId;
			});
			if (input.putBomb && bombsInMap < stats.maxBombs)
				_world->spawnBombSystem(player);
			input.putBomb = false;
		}
	}
}