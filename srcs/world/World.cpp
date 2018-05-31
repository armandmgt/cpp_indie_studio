/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** world
*/
#include <engine/Components.hpp>
#include "world/World.hpp"

ecs::entityId ecs::world::createEntity(ecs::entityType type)
{
	static std::unordered_map<entityType, std::bitset<Entity::bitSize>> map {
		{PLAYER, },
		{POWERUP, },
		{BOMB, },
		{WALL, },
		{FLAMME, }
	};
	return _world.size() - 1;
}

void ecs::world::destroyEntity(ecs::entityId id)
{
}
