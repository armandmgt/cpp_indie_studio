/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** AMenu
*/

#include "menu/AMenu.hpp"
#include "common/vec.hpp"

ids::menu::AMenu::AMenu(std::shared_ptr<gfx::Renderer> rend, std::shared_ptr<ids::Music> music, sceneId id)
	: _rend(rend), _musicManager(music), _posBackground(0,0), _id(id), _mouseData()
{
}

ids::menu::AMenu::~AMenu()
{
	_rend->remove2D(_backgroundImg);
	std::for_each(_infoButtons.begin(), _infoButtons.end(), [this](Button &button) {
		_rend->remove2D(button.inactive);
		_rend->remove2D(button.active);
		_rend->remove2D(button.active);
	});
}

bool	ids::menu::AMenu::setWindow()
{
	_rend->load2D(_backgroundImg, _posBackground);
	for (auto &button : _infoButtons) {
		_rend->load2D(button.inactive, button.pos);
	}
	return true;
}

bool ids::menu::AMenu::insideRect(vec2d<int> &pos, vec2d<int> &size)
{
	return _mouseData.position.X >= pos.x && _mouseData.position.X < pos.x + size.x
	    && _mouseData.position.Y >= pos.y && _mouseData.position.Y < pos.y + size.y;
}

void ids::menu::AMenu::buttonEvent()
{
	for (auto &button : _infoButtons) {
		if (insideRect(button.pos, button.size)) {
			if (!button.hovered) {
				_rend->remove2D(button.inactive);
				_rend->load2D(button.active, button.pos);
				button.hovered = true;
			}
			if (_mouseData.leftButtonDown) {
				_id = button.action;
			}
		} else if (button.hovered) {
			button.hovered = false;
			_rend->remove2D(button.active);
			_rend->load2D(button.inactive, button.pos);
		}
	}
}
