/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ParseInput
*/

#include "engine/systems/ParseInputSystem.hpp"

ecs::ParseInput::ParseInput(entityVector allEntities, evt::MyEventReceiver &e, ids::PlayerAI &ai1, ids::PlayerAI &ai2)
	: System(allEntities), event(e), _ai1(ai1), _ai2(ai2)
{
}

void ecs::ParseInput::update(double delta[[maybe_unused]]) {
	auto entities = getEntities(COMP_CHARACTER, COMP_INPUT);

	for (auto &e : entities) {
		auto &inputPlayer = e->getComponent<Input>();
		auto id = e->getComponent<Character>().id;
		std::queue<evt::Event> events;
		if (!inputPlayer.isAi)
			events = event.getPlayerEvent(id);
		else
			events.push((id == 0 ? _ai1 : _ai2).computeAction());
		while (!events.empty()) {
			auto &event = events.front();
			if (event.action == evt::MOVEUP)
				inputPlayer.goUp = true;
			if (event.action == evt::MOVEDOWN)
				inputPlayer.goDown = true;
			if (event.action == evt::MOVELEFT)
				inputPlayer.goLeft = true;
			if (event.action == evt::MOVERIGHT)
				inputPlayer.goRight = true;
			if (event.action == evt::PUTBOMB)
				inputPlayer.putBomb = true;
			events.pop();
		}
	}
}