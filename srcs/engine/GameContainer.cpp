/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** GameContainer
*/

#include "engine/GameContainer.hpp"

ids::GameContainer::GameContainer() : _ge()
{
}

ids::GameContainer::~GameContainer()
{
}

ids::GameContainer *ids::GameContainer::create()
{
	return new GameContainer();
}

void ids::GameContainer::start()
{
}
