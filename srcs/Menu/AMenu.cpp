/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** AMenu
*/

#include <vector>
#include "menu/AMenu.hpp"
#include "common/vec.hpp"

ids::menu::AMenu::AMenu(shared_ptr<Renderer> rend) : _rend(rend)
{
	_posBackground.push_back({1920,1080});
	_posBackground.push_back({0,0});
}

bool ids::menu::AMenu::setWindow()
{
	_rend.load2D("/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/backgound/menu-background.png", _posBackground);
}

ids::menu::AMenu::SceneId ids::menu::AMenu::getSceneId()
{

}

void ids::menu::AMenu::computeEvent()
{

}
