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

		for (auto &player : entities) {
			auto &input = player->getComponent<Input>();
			if (input.putBomb) {
				_world->spawnBombSystem(player);
				input.putBomb = false;
			}
		}
	}
}