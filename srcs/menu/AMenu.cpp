/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** AMenu
*/

#include "menu/AMenu.hpp"
#include "common/vec.hpp"

ids::menu::AMenu::AMenu(gfx::Renderer *rend, sceneId id, ids::Music *music) : _rend(rend), _posBackground(0,0), _id(id),
	_mouse{{0,0}, false}, _musicManager(music)
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

bool ids::menu::AMenu::inside_rect(vec2d<int> &pos, vec2d<int> &size)
{
	return _mouse.pos.x >= pos.x && _mouse.pos.x < pos.x + size.x
	    && _mouse.pos.y >= pos.y && _mouse.pos.y < pos.y + size.y;
}

void ids::menu::AMenu::buttonEvent()
{
	for (auto &button : _infoButtons) {
		if (inside_rect(button.pos, button.size)) {
				_rend->remove2D(button.inactive);
				_rend->load2D(button.active, button.pos);
				if (_mouse.state) {
					_id = button.action;
				}
				button.hovered = true;
			}
		else if (button.hovered) {
			button.hovered = false;
			_rend->remove2D(button.active);
			_rend->load2D(button.inactive, button.pos);
		}
	}
}

void	ids::menu::AMenu::computeEvent(evt::MyEventReceiver::MouseState &mouseData)
{
	_mouse.pos = {mouseData.position.X, mouseData.position.Y};
	_mouse.state = mouseData.leftButtonDown;
	buttonEvent();
}
