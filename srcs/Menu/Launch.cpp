/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Launch
*/

#include "menu/Launch.hpp"

ids::menu::Launch::Launch(gfx::Renderer *rend) : AMenu(rend)
{
	_items.emplace_back((struct items){"bomberman", 0, "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/Items/bomber-man.png", vec2d<int>(600, 400)});
	_items.emplace_back((struct items){"speak-bubble", 5, "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/Items/speak-bubble.png", vec2d<int>(1350, 450)});
	_items.emplace_back((struct items){"welcome-message", 5, "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/Items/welcome-message.png", vec2d<int>(1410, 530)});
	decorateScene();
}

void ids::menu::Launch::decorateScene()
{
	for (auto &button : _infoButtons) {
		_rend->load2D(button.inactive, button.pos);
	}
	for (auto &item : _items) {
		_rend->load2D(item.path, item.pos);
	}
}
