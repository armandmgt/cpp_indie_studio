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

	void world::_spawnEntitiesFromMap(std::vector<std::string> &&gameMap) {
		for (auto itR = gameMap.begin(); itR != gameMap.end(); itR++) {
			for (auto itC = itR->begin(); itC != itR->end(); itC++) {
				switch (*itC) {
					case '*':
						this->_spawnWall(itC - itR->begin(), itR - gameMap.begin());
						break;
					default:
						throw std::logic_error("Invalid entity in map");

				}
			}
		}
	}

	void world::_spawnWall(size_t posX, size_t posY) {
		Position pos = { static_cast<float>(posX), static_cast<float>(posY) };
		Destructible des = { true, nullptr };

		createEntity(WALL, pos, des);
	}
}
