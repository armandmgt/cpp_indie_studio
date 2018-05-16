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
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	return false;
}

bool gfx::MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}
