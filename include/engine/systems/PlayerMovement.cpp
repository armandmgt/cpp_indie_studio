/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PlayerMovement
*/
#include <iostream>
#include "PlayerMovement.hpp"

namespace ecs {
	PlayerMovement::PlayerMovement(std::vector<Entity> *allEntities, evt::MyEventReceiver &e) :
		System(allEntities), _eventReceiver(e) {}

	void PlayerMovement::update(double delta[[maybe_unused]]) {
		auto &entities = getEntities(COMP_CHARACTER, COMP_VELOCITY);

		for (std::size_t i = 0; i < 4; i++) {
			auto playerEvent = _eventReceiver.getPlayerEvent(i, evt::MOVEMENT);
			while (!playerEvent.empty()) {
				std::cout << "Player " << i << " event : " << playerEvent.front().action << std::endl;
				playerEvent.pop();
			}
		}

		for (auto e : entities) {
			auto &position = e->getComponent<Position>();
			auto &velocity = e->getComponent<Velocity>();
			position.x += velocity.x;
			position.y += velocity.y;
		}


	}

}