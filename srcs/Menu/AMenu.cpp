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

ids::menu::AMenu::AMenu(gfx::Renderer *rend) : _rend(rend), _posBackground(0,0), _mousePos(0,0)
{
	_infoButtons.emplace_back((struct button){vec2d<int>(1570,670), vec2d<int>(107,55), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/play-button.png",
				   "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-play-button.png", GAME, false});
	_infoButtons.emplace_back((struct button){vec2d<int>(1520,750), vec2d<int>(195,53), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/scores-button.png",
				  "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-scores-button.png", SCORE, false});
	_infoButtons.emplace_back((struct button){vec2d<int>(1500,820), vec2d<int>(235,64), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/settings-button.png",
						  "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-settings-button.png", SETTINGS, false});
	_infoButtons.emplace_back((struct button){vec2d<int>(1570,900), vec2d<int>(101,63), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/quit-button.png",
					  "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-quit-button.png", QUIT, false});
	setWindow();
}

bool	ids::menu::AMenu::setWindow()
{
	_rend->load2D("/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/backgound/menu-background.png", _posBackground);
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
	std::cout << mousePos.x << " " << mousePos.y << std::endl;

	buttonEvent();
}
