/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ExplosionSystem
*/

#include <iostream>
#include "ExplosionSystem.hpp"

ecs::ExplosionSystem::ExplosionSystem(entityVector allEntities, gfx::Renderer *render,
	std::shared_ptr<ecs::World> world
) : System(allEntities), _renderer(render), _world(world)
{
}

void ecs::ExplosionSystem::update(double delta[[maybe_unused]]) {
	auto bombs = getEntities(COMP_POSITION, COMP_EXPLOSION);

	for (auto &bomb : bombs) {
		auto &ephemereComp = bomb->getComponent<Ephemere>();
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = now - ephemereComp.time;
		if (diff.count() > ephemereComp.timeout) {
			_world->spawnFlames(bomb->getComponent<Position>(), bomb->getComponent<Explosion>().power);
			_world->destroyEntity(bomb->id);
		}
	}
}