/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventReceiver
*/

#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
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

bool evt::MyEventReceiver::_fillKey()
{
	static std::unordered_map<irr::EKEY_CODE, evt::PlayerEvent> const mapEvent {
		{irr::KEY_KEY_O, {1, {evt::MOVEMENT, evt::MOVEUP, evt::UP}}},
		{irr::KEY_KEY_L, {1, {evt::MOVEMENT, evt::MOVEDOWN, evt::DOWN}}},
		{irr::KEY_KEY_M, {1, {evt::MOVEMENT, evt::MOVERIGHT, evt::RIGHT}}},
		{irr::KEY_KEY_K, {1, {evt::MOVEMENT, evt::MOVELEFT, evt::LEFT}}},
		{irr::KEY_KEY_I, {1, {evt::ACTION, evt::PUTBOMB, evt::I}}},
		{irr::KEY_DELETE, {1, {evt::ACTION, evt::RESTART, evt::DELETE}}},
		{irr::KEY_ESCAPE, {1, {evt::ACTION, evt::QUIT, evt::ESCAPE}}},
		{irr::KEY_LBUTTON, {1, {evt::ACTION, evt::CLICK, evt::MOUSE}}},
		{irr::KEY_KEY_A, {2, {evt::ACTION, evt::PUTBOMB, evt::A}}},
		{irr::KEY_KEY_D, {2, {evt::MOVEMENT, evt::MOVERIGHT, evt::D}}},
		{irr::KEY_KEY_Q, {2, {evt::MOVEMENT, evt::MOVELEFT, evt::Q}}},
		{irr::KEY_KEY_S, {2, {evt::MOVEMENT, evt::MOVEDOWN, evt::S}}},
		{irr::KEY_KEY_Z, {2, {evt::MOVEMENT, evt::MOVEUP, evt::Z}}},
		{irr::KEY_SPACE, {1, {evt::MOVEMENT, evt::PAUSE, evt::SPACE}}}
	};

	for (auto &keyCode : keyboardPressed) {
		auto playerEvent = mapEvent.find(keyCode);
		if (playerEvent != mapEvent.end()) {
			auto &event = playerEvent->second;
			buffer.emplace(event.id, event.event);
		}
	}
	return !keyboardPressed.empty();
}

std::queue<evt::Event> evt::MyEventReceiver::getPlayerEvent(std::size_t id)
{
	std::queue<evt::Event> eventQueue;

	for (auto eventIt = buffer.begin(); eventIt != buffer.end();) {
		if (eventIt->first == id) {
			eventQueue.push(eventIt->second);
		}
		eventIt++;
	}
	for (auto eventIt = buffer.begin(); eventIt != buffer.end(); ) {
		if (eventIt->first == id)
			eventIt = buffer.erase(eventIt);
		else
			eventIt++;
	}
	return eventQueue;
}

bool evt::MyEventReceiver::hasEvent()
{
	irr::EKEY_CODE  keyCode;

	if (getKeyPressed(keyCode)) {
		_fillKey();
		return !buffer.empty();
	}
	return false;
}

bool evt::MyEventReceiver::getKeyPressed(irr::EKEY_CODE &keyCode)
{
	keyboardPressed.clear();
	for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++) {
		if (isKeyDown(static_cast<irr::EKEY_CODE>(i))) {
			keyboardPressed.push_back(static_cast<irr::EKEY_CODE>(i));
			keyCode = static_cast<irr::EKEY_CODE>(i);
		}
	}
	return !keyboardPressed.empty();
}
