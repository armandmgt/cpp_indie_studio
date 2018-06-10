/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ParseInput
*/

#include "engine/systems/ParseInputSystem.hpp"

ecs::ParseInput::ParseInput(entityVector allEntities, evt::MyEventReceiver &e, ids::PlayerAI &ai1, ids::PlayerAI &ai2)
	: System(allEntities), event(e), _ai1(ai1), _ai2(ai2 )
{
}

void ecs::ParseInput::update(double delta[[maybe_unused]]) {
	auto entities = getEntities(COMP_CHARACTER, COMP_INPUT);

	for (auto &e : entities) {
		auto &InputPlayer = e->getComponent<Input>();
		auto events = event.getPlayerEvent(e->getComponent<Character>().id);
		if (events.empty()) {
			events.push(_ai1.computeAction());
			events.push(_ai2.computeAction());
		}
		while (!events.empty()) {
			auto &event = events.front();
			if (event.action == evt::MOVEUP)
				InputPlayer.goUp = true;
			if (event.action == evt::MOVEDOWN)
				InputPlayer.goDown = true;
			if (event.action == evt::MOVELEFT)
				InputPlayer.goLeft = true;
			if (event.action == evt::MOVERIGHT)
				InputPlayer.goRight = true;
			if (event.action == evt::PUTBOMB)
				InputPlayer.putBomb = true;
			events.pop();
		}
	}
}