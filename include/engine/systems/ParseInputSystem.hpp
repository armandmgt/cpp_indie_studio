/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ParseInput
*/

#pragma once

#include "event/EventReceiver.hpp"
#include "engine/ai/PlayerAI.hpp"
#include "Systems.hpp"

namespace ecs {
	class ParseInput : public System {
	public:
		ParseInput(entityVector allEntities, evt::MyEventReceiver &e, ids::PlayerAI &ai1, ids::PlayerAI &ai2);

		void update(double delta) override;

	private:
		evt::MyEventReceiver &event;
		ids::PlayerAI &_ai1;
		ids::PlayerAI &_ai2;
	};
};
