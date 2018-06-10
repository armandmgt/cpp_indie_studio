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
	auto destructibles = getEntities(COMP_DESTRUCTIBLE, COMP_POSITION);
	auto flames = getEntities(COMP_DAMAGE, COMP_POSITION);

	for (auto &flame : flames) {
		auto &posFlame = flame->getComponent<Position>();
		for (auto &destructible : destructibles) {
			auto &posDestructible = destructible->getComponent<Position>();
			vec2d<float> roundedPos = roundPos<float>(posDestructible.x, posDestructible.y);
			if (roundedPos.x == posFlame.x && roundedPos.y == posFlame.y) {
				if (destructible->getComponent<Destructible>().item)
					_world->spawnCollectibleFromBox(destructible);
				_world->destroyEntity(destructible->id);
				destructibles.erase(std::remove(destructibles.begin(), destructibles.end(),
					destructible));
			}
		}
	}
}