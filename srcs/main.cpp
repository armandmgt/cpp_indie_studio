/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <string>
#include <iostream>
#include <memory>
#include "engine/GameContainer.hpp"
#include "world/World.hpp"
#include "map/Map.hpp"

int main()
{
	ecs::world ecs;
	Map map(20, 20);
	map.initMap(20);

	ecs._spawnEntitiesFromMap(std::move(map.getMap()));
	ecs.drawEntities();

	return 0;
}
