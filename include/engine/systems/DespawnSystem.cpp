#include "DespawnSystem.hpp"/*
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
	auto &entities = getEntities(COMP_EPHEMERE, COMP_GRAPHIC);

	std::cout << "how many flames ? " << entities.size() << std::endl;
	for (auto &e : entities) {
		auto &exp = e->getComponent<Ephemere>();
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = now - exp.time;
		std::cout << "Time : " << diff.count() << std::endl;
		if (diff.count() > exp.timeout) {
			e->getComponent<Graphic>().sceneNode->remove();
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