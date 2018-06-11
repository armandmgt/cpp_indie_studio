/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PlayerMovement
*/

#include "engine/systems/PlayerMovement.hpp"

namespace ecs {
	PlayerMovement::PlayerMovement(entityVector allEntities) : System(allEntities)
	{
	}

	void PlayerMovement::update(double delta[[maybe_unused]]) {
		auto entities = getEntities(COMP_CHARACTER, COMP_VELOCITY, COMP_INPUT);

		for (auto &player : entities) {
			auto &input = player->getComponent<Input>();
			auto &stats = player->getComponent<Character>();
			auto &velocityPlayer = player->getComponent<Velocity>();
			if (input.goDown) {
				velocityPlayer.y -= 0.1 * stats.speed;
				input.goDown = false;
			}
			if (input.goUp) {
				velocityPlayer.y += 0.1 * stats.speed;
				input.goUp = false;
			}
			if (input.goLeft) {
				velocityPlayer.x -= 0.1 * stats.speed;
				input.goLeft = false;
			}
			if (input.goRight) {
				velocityPlayer.x += 0.1 * stats.speed;
				input.goRight = false;
			}
		}
	}
}