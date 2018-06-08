/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** AMenu
*/

#include "menu/AMenu.hpp"
#include "common/vec.hpp"

ids::menu::AMenu::AMenu(gfx::Renderer *rend, sceneId id, ids::Music *music) : _rend(rend), _posBackground(0,0), _id(id),
	_mousePos(vec2d<int>(0,0), false), _musicManager(music)
{
}

bool	ids::menu::AMenu::setWindow()
{
	_rend->load2D(_backgroundImg, _posBackground);
	for (auto &button : _infoButtons) {
		_rend->load2D(button.inactive, button.pos);
	}
	return true;
}

void ids::menu::AMenu::buttonEvent()
{
	for (auto &button : _infoButtons) {
		if (_mousePos.first.x >= button.pos.x && _mousePos.first.x < button.pos.x + button.size.x
			&& _mousePos.first.y >= button.pos.y && _mousePos.first.y < button.pos.y + button.size.y) {
				_rend->load2D(button.active, button.pos);
				if (_mousePos.second) {
					_id = button.action;
				}
				button.hovered = true;
			}
		else if (button.hovered) {
			button.hovered = false;
			_rend->load2D(button.inactive, button.pos);
		}
	}
}

void	ids::menu::AMenu::computeEvent(evt::MyEventReceiver::MouseState &mouseData)
{
	_mousePos.first = {mouseData.position.X, mouseData.position.Y};
	_mousePos.second = mouseData.leftButtonDown;
	buttonEvent();
}
