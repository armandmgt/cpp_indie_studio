/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** world
*/
#include <engine/Components.hpp>
#include "world/World.hpp"

namespace ecs {
	entityId world::createEntity(entityType type) {
		static std::unordered_map<entityType, std::bitset<Entity::bitSize>> map {
			{PLAYER, COMP_POSITION | COMP_VELOCITY | COMP_CHARACTER | COMP_DESTRUCTIBLE},
			{POWERUP, COMP_POSITION | COMP_COLLECTIBLE},
			{BOMB, COMP_VELOCITY | COMP_EXPLOSION},
			{WALL, COMP_POSITION | COMP_DESTRUCTIBLE},
			{FLAMME, COMP_POSITION}
		};
		return _world.size() - 1;
	}

	void world::destroyEntity(entityId id) {
	}
}
