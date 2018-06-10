/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ParseInput
*/

#pragma once

#include "event/EventReceiver.hpp"
#include "Systems.hpp"

namespace ecs {
	class ParseInput : public System {
	public:
		ParseInput(entityVector allEntities, evt::MyEventReceiver &e);

		void update(double delta) override;

	private:
		evt::MyEventReceiver &event;
	};
};
