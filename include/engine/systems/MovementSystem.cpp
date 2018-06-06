/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MovementSystem
*/

#include "MovementSystem.hpp"

namespace ecs {
	MovementSystem::MovementSystem(std::vector<Entity> *allEntities) : System(allEntities)
	{
	}

	void MovementSystem::update(double delta[[maybe_unused]]) {
		auto &entities = getEntities(COMP_POSITION, COMP_VELOCITY);

		for (auto e : entities) {
			auto &position = e->getComponent<Position>();
			auto &velocity = e->getComponent<Velocity>();
			position.x += velocity.x;
			position.y += velocity.y;
		}
	}
};