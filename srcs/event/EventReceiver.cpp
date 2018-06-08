/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventReceiver
*/

#include <iostream>
#include <unordered_map>
#include "event/EventReceiver.hpp"

evt::MyEventReceiver::MyEventReceiver()
{
	for (bool &i : keyIsDown)
		i = false;
}

bool evt::MyEventReceiver::OnEvent(irr::SEvent const &event)
{
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
			case (irr::EMIE_LMOUSE_PRESSED_DOWN):
				mouseState.leftButtonDown = true;
				break;
			case (irr::EMIE_LMOUSE_LEFT_UP):
				mouseState.leftButtonDown = false;
				break;
			case (irr::EMIE_MOUSE_MOVED):
				mouseState.position.X = event.MouseInput.X;
			mouseState.position.Y = event.MouseInput.Y;
				break;
			default:
				break;
		}
	}
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	return false;
}

bool evt::MyEventReceiver::isKeyDown(irr::EKEY_CODE keyCode) const
{
	return keyIsDown[keyCode];
}

const evt::MyEventReceiver::MouseState &evt::MyEventReceiver::getMousePosition() const
{
	return mouseState;
}

bool evt::MyEventReceiver::_fillKey(irr::EKEY_CODE &keyCode)
{
	static std::unordered_map<irr::EKEY_CODE, std::pair<std::size_t, evt::eventType>> const mapEvent {
		{irr::KEY_UP, {1, {evt::MOVEUP, evt::UP}}},
		{irr::KEY_DOWN, {1, {evt::MOVEDOWN, evt::DOWN}}},
		{irr::KEY_RIGHT, {1, {evt::MOVERIGHT, evt::RIGHT}}},
		{irr::KEY_LEFT, {1, {evt::MOVELEFT, evt::LEFT}}},
		{irr::KEY_DELETE, {1, {evt::RESTART, evt::DELETE}}},
		{irr::KEY_ESCAPE, {1, {evt::QUIT, evt::ESCAPE}}},
		{irr::KEY_LBUTTON, {1, {evt::CLICK, evt::MOUSE}}},
		{irr::KEY_KEY_A, {2, {evt::PUTBOMB, evt::A}}},
		{irr::KEY_KEY_D, {2, {evt::MOVERIGHT, evt::D}}},
		{irr::KEY_KEY_Q, {2, {evt::MOVELEFT, evt::Q}}},
		{irr::KEY_KEY_S, {2, {evt::MOVEDOWN, evt::S}}},
		{irr::KEY_KEY_Z, {2, {evt::MOVEUP, evt::Z}}},
		{irr::KEY_SPACE, {1, {evt::PAUSE, evt::SPACE}}}
	};

	auto value = mapEvent.find(keyCode);
	if (value == mapEvent.end())
		return false;
	buffer.emplace(mapEvent.at(keyCode));
	return true;
}

std::queue<evt::eventType> evt::MyEventReceiver::getPlayerEvent(std::size_t playerId)
{
	std::queue<evt::eventType> eventQueue;

	std::multimap<std::size_t, evt::eventType>::iterator eventIt;
	while ((eventIt = buffer.find(playerId)) != buffer.end()) {
		eventQueue.push(eventIt->second);
		buffer.erase(eventIt);
	}
	return eventQueue;
}

bool evt::MyEventReceiver::pollEvent()
{
	irr::EKEY_CODE  keyCode;

	if (getKeyPressed(keyCode)) {
		_fillKey(keyCode);
		return !buffer.empty();
	}
	return false;
}

bool evt::MyEventReceiver::getKeyPressed(irr::EKEY_CODE &keyCode) const
{
	for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++) {
		if (isKeyDown(static_cast<irr::EKEY_CODE>(i))) {
			keyCode = static_cast<irr::EKEY_CODE>(i);
			return true;
		}
	}
	return false;
}
