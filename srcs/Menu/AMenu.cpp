/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** AMenu
*/

#include <vector>
#include "menu/AMenu.hpp"
#include "common/vec.hpp"

ids::menu::AMenu::AMenu(std::shared_ptr<gfx::Renderer> rend) : _rend(rend), _posBackground(0,0)
{
	setWindow();
}

bool	ids::menu::AMenu::setWindow()
{
	_rend->load2D("/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/backgound/menu-background.png", _posBackground);
}

ids::menu::AMenu::SceneId	ids::menu::AMenu::getSceneId()
{

}

void	ids::menu::AMenu::computeEvent()
{

}
