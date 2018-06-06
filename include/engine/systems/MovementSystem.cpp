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

	void MovementSystem::update(double delta) {
		auto &entities = getEntities(COMP_POSITION, COMP_VELOCITY);

		std::cout << "There are " << entities.size() << " entities with a position and velocity component"
			<< std::endl;
	}
};