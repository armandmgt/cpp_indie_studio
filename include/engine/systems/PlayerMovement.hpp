/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PlayerMovement
*/

#pragma once

#include "event/EventReceiver.hpp"
#include "Systems.hpp"

namespace ecs {
	class PlayerMovement : public System {
	public:
		explicit PlayerMovement(std::vector<Entity> *, evt::MyEventReceiver &e);

		void update(double delta) override;

	private:
		evt::MyEventReceiver &_eventReceiver;
	};
};
