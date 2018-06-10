/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** BreakDestructibleSystem
*/

#include <iostream>
#include "BreakDestructibleSystem.hpp"

ecs::BreakDestructibleSystem::BreakDestructibleSystem(entityVector allEntities, gfx::Renderer *render,
				      std::shared_ptr<ecs::World> world
) : System(allEntities), _renderer(render), _world(world)
{
}

void ecs::BreakDestructibleSystem::update(double delta[[maybe_unused]]) {
	auto &boxes = getEntities(COMP_DESTRUCTIBLE);
	auto &flames = getEntities(COMP_DAMAGE, COMP_POSITION);

	for (auto &flame : flames) {
		auto &posFlame = flame->getComponent<Position>();
		for (auto &box : boxes) {
			auto &posBox = box->getComponent<Position>();
			if (posBox.x == posFlame.x && posBox.y == posFlame.y) {
				std::cout << "I'm flamme on box" << std::endl;
				_world->spawnCollectibleFromBoxSystem(box);
				for (auto it = _allEntities->begin(); it != _allEntities->end(); ) {
					if ((*it)->id == box->id)
						it = _allEntities->erase(it);
					else
						++it;
				}
				_world->destroyEntity(box->id);

			}
		}
	}
}