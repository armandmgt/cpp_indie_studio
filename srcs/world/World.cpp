/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** world
*/
#include <engine/Components.hpp>
#include <functional>
#include "world/World.hpp"

namespace ecs {

	entityId world::createEntity(entityType type) {
		static std::unordered_map<entityType, std::function<void()>> map {
			{PLAYER, createPlayer},
			{POWERUP, createPowerUp},
			{BOMB, createBomb},
			{WALL, createWall},
			{FLAMME, createFlamme}
		};
		map[type];
		return _world.size() - 1;
	}

	void world::destroyEntity(entityId id) {
	}

	void world::createPlayer() {
		_world.emplace(_world.size() - 1, COMP_POSITION | COMP_VELOCITY | COMP_CHARACTER | COMP_DESTRUCTIBLE);
	}

	void world::createPowerUp() {
		_world.emplace(_world.size() - 1, COMP_POSITION | COMP_COLLECTIBLE);
	}

	void world::createBomb() {
		_world.emplace(_world.size() - 1, COMP_VELOCITY | COMP_EXPLOSION);
	}

	void world::createWall() {
		_world.emplace(_world.size() - 1, COMP_POSITION | COMP_DESTRUCTIBLE);
	}

	void world::createFlamme() {
		_world.emplace(_world.size() - 1, COMP_POSITION);
	}
}
