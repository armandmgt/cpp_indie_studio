/*
** EPITECH PROJECT, 2018
** Event
** File description:
** none
*/

#include <iterator>
#include <irrlicht/Keycodes.h>
#include <iostream>
#include "event/Event.hpp"

ids::Event::Event(gfx::Renderer &window) noexcept : renderer(window)
{
}

bool ids::Event::_fillKey(irr::EKEY_CODE &keyCode)
{
	static std::unordered_map<irr::EKEY_CODE, std::pair<std::size_t, eventType>> const MapEvent {
		{irr::KEY_UP, {1, {MOVEUP, UP}}},
		{irr::KEY_DOWN, {1, {MOVEDOWN, DOWN}}},
		{irr::KEY_RIGHT, {1, {MOVERIGHT, RIGHT}}},
		{irr::KEY_LEFT, {1, {MOVELEFT, LEFT}}},
		{irr::KEY_DELETE, {1, {RESTART, DELE}}},
		{irr::KEY_ESCAPE, {1, {QUIT, ESCAPE}}},
		{irr::KEY_LBUTTON, {1, {CLICK, MOUSE}}},
		{irr::KEY_KEY_A, {2, {PUTBOMB, A}}},
		{irr::KEY_KEY_D, {2, {MOVERIGHT, D}}},
		{irr::KEY_KEY_E, {2, {PUTITEM, E}}},
		{irr::KEY_KEY_Q, {2, {MOVELEFT, Q}}},
		{irr::KEY_KEY_S, {2, {MOVEDOWN, S}}},
		{irr::KEY_KEY_Z, {2, {MOVEUP, Z}}},
		{irr::KEY_SPACE, {1, {PAUSE, SPACE}}}
	};

	auto value = MapEvent.find(keyCode);
	if (value == MapEvent.end())
		return false;
	buffer.emplace(MapEvent.at(keyCode));
	for (auto &it : buffer) {
		std::cout << it.first << " = [" << it.second.key << ", " << it.second.action << "]" << std::endl;
	}
	return true;
}

std::queue<ids::eventType> ids::Event::getEvent(std::size_t index)
{
	std::queue<ids::eventType> eventQueue;

	auto event = buffer.begin();
	for (; event != buffer.end() ;) {
		event = buffer.find(index);
		eventQueue.push(event->second);
		 event = buffer.erase(event);
	}
	return eventQueue;
}

bool ids::Event::pollEvent()
{
	irr::EKEY_CODE  keyCode;

	if (renderer.getKeyPressed(keyCode)) {
		_fillKey(keyCode);
		return !buffer.empty();
	}
	return false;
}