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
	auto &entities = getEntities(COMP_POSITION, COMP_EXPLOSION);

	for (auto &e : entities) {
		auto &exp = e->getComponent<Explosion>();
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = now - exp.time;
		if (diff.count() > exp.timeout) {
			e->getComponent<Graphic>().sceneNode->remove();
			_world->spawnFlames(e->getComponent<Position>(), e->getComponent<Explosion>().power);
			for (auto it = _allEntities->begin(); it != _allEntities->end(); ) {
				if ((*it)->id == e->id)
					it = _allEntities->erase(it);
				else
					++it;
			}
			_world->destroyEntity(e->id);
		}
	}
}