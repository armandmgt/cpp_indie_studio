/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PlayerMovement
*/

#include <iostream>
#include "PlayerMovement.hpp"

namespace ecs {
	PlayerMovement::PlayerMovement(std::vector<Entity> *allEntities, gfx::Renderer *gfx, evt::MyEventReceiver &e) :
		System(allEntities, gfx), _eventReceiver(e) {}

	void PlayerMovement::update(double delta[[maybe_unused]]) {
		auto &entities = getEntities(COMP_CHARACTER, COMP_VELOCITY);

		for (auto &player : entities) {
			auto playerEvent = _eventReceiver.getPlayerEvent(player->getComponent<Character>().id, evt::MOVEMENT);
			while (!playerEvent.empty()) {
				if (playerEvent.front().action == evt::MOVEUP) {
					auto &playerVel = player->getComponent<Velocity>();
					playerVel.x += 0.1;
					std::cout << "now Vel::x equal to " << player->getComponent<Velocity>().x <<
					        std::endl;
				}
				playerEvent.pop();
			}
		}
	}
}