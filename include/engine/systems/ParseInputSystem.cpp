#include <iostream>
#include "ParseInputSystem.hpp"/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ParseInput
*/

#include "ParseInputSystem.hpp"

ecs::ParseInput::ParseInput(std::vector<ecs::Entity> *allEntities, evt::MyEventReceiver &e)
	: System(allEntities), event(e) {}

void ecs::ParseInput::update(double delta[[maybe_unused]]) {
	auto &entities = getEntities(COMP_CHARACTER, COMP_INPUT);

	for (auto &e : entities) {
		auto &InputPlayer = e->getComponent<Input>();
		auto events = event.getPlayerEvent(e->getComponent<Character>().id);
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
			std::cout << "InputPlayer : \n\tGo Up : " << InputPlayer.goUp << "\n\tGo Down : " << InputPlayer
				.goDown <<
				  "\n\tGo Left : " << InputPlayer.goLeft << "\n\tGo Right : " << InputPlayer.goRight <<
				  "\n\tPut bomb : " << InputPlayer.putBomb <<
				  std::endl;
			events.pop();
		}
	}
}