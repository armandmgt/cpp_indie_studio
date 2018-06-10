/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** DisparitionFlammeSystem
*/

#include <iostream>
#include "DespawnSystem.hpp"

ecs::DespawnSystem::DespawnSystem(entityVector allEntities, gfx::Renderer *render, std::shared_ptr<ecs::World> world)
	: System(allEntities), _renderer(render), _world(world)
{
}

void ecs::DespawnSystem::update(double delta[[maybe_unused]]) {
	auto ephemereEntities = getEntities(COMP_EPHEMERE, COMP_GRAPHIC);

	for (auto &ephemere : ephemereEntities) {
		auto &ephemereComp = ephemere->getComponent<Ephemere>();
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = now - ephemereComp.time;
		if (diff.count() > ephemereComp.timeout) {
			_world->destroyEntity(ephemere->id);
		}

	}
}