/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventReceiver
*/
#include <iostream>
#include "gfx/EventReceiver.hpp"

gfx::MyEventReceiver::MyEventReceiver()
{
	for (bool &i : KeyIsDown)
		i = false;
}

bool gfx::MyEventReceiver::OnEvent(irr::SEvent const &event)
{
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
			case (irr::EMIE_LMOUSE_PRESSED_DOWN):
				MouseState.LeftButtonDown = true;
				break;
			case (irr::EMIE_LMOUSE_LEFT_UP):
				MouseState.LeftButtonDown = false;
				break;
			case (irr::EMIE_MOUSE_MOVED):
				MouseState.position.X = event.MouseInput.X;
				MouseState.position.Y = event.MouseInput.Y;
				break;
			default:
				break;
		}
	}
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	return false;
}

bool gfx::MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

const gfx::MyEventReceiver::SMouseState &gfx::MyEventReceiver::GetMouseState() const
{
	return MouseState;
}