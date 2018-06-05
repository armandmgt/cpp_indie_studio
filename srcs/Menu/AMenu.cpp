/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** AMenu
*/

#include <vector>
#include <iostream>
#include "menu/AMenu.hpp"
#include "common/vec.hpp"

ids::menu::AMenu::AMenu(gfx::Renderer *rend, SceneId id) : _rend(rend), _posBackground(0,0), _mousePos(0,0), _id(id)
{
	std::cout << "here\n";

}

bool	ids::menu::AMenu::setWindow()
{
	_rend->load2D(_backgroundImg, _posBackground);
	for (auto &button : _infoButtons) {
		_rend->load2D(button.inactive, button.pos);
	}
	return true;
}

ids::menu::AMenu::SceneId	ids::menu::AMenu::getSceneId()
{
	return _id;
}

bool ids::menu::AMenu::buttonEvent()
{
	for (auto &button : _infoButtons) {
		if (_mousePos.x >= button.pos.x && _mousePos.x < button.pos.x + button.size.x
			&& _mousePos.y >= button.pos.y && _mousePos.y < button.pos.y + button.size.y) {
				_rend->load2D(button.active, button.pos);
				_id = button.action;
				button.hovered = true;

			}
		else if (button.hovered) {
			button.hovered = false;
			_rend->load2D(button.inactive, button.pos);
		}
	}
	return false;
}

void	ids::menu::AMenu::computeEvent(vec2d<int> &mousePos)
{
	_mousePos = mousePos;
	buttonEvent();
}
