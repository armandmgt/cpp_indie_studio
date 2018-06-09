/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PlayerMovement
*/

#include <iostream>
#include "PlayerMovement.hpp"

namespace ecs {
	PlayerMovement::PlayerMovement(std::vector<Entity> *allEntities) :
		System(allEntities) {}

	void PlayerMovement::update(double delta[[maybe_unused]]) {
		auto &entities = getEntities(COMP_CHARACTER, COMP_VELOCITY, COMP_INPUT);

		for (auto &player : entities) {
			auto &input = player->getComponent<Input>();
			auto &velocityPlayer = player->getComponent<Velocity>();
			if (input.goDown) {
				velocityPlayer.x -= 0.1;
			}
			if (input.goUp) {
				velocityPlayer.x += 0.1;
			}
			if (input.goLeft) {
				velocityPlayer.y -= 0.1;
			}
			if (input.goRight) {
				velocityPlayer.y += 0.1;
			}
		}
	}
}