/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include "menu/AMenu.hpp"
#include "gfx/Renderer.hpp"

int main()
{
	make_shared<Renderer>  rend;
	ids::menu::AMenu(rend);
}