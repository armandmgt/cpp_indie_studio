/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventReceiver
*/

#include "gfx/EventReceiver.hpp"

gfx::MyEventReceiver::MyEventReceiver()
{
	for (bool &i : keyIsDown)
		i = false;
}

bool gfx::MyEventReceiver::OnEvent(irr::SEvent const &event)
{
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
			case (irr::EMIE_LMOUSE_PRESSED_DOWN):
				mouseState.LeftButtonDown = true;
				break;
			case (irr::EMIE_LMOUSE_LEFT_UP):
				mouseState.LeftButtonDown = false;
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

bool gfx::MyEventReceiver::isKeyDown(irr::EKEY_CODE keyCode) const
{
	return keyIsDown[keyCode];
}

const gfx::MyEventReceiver::SMouseState &gfx::MyEventReceiver::getMouseState() const
{
	return mouseState;
}