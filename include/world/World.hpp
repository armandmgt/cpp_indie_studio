/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** world
*/

#ifndef CPP_INDIE_STUDIO_WORLD_HPP
#define CPP_INDIE_STUDIO_WORLD_HPP

#include <unordered_map>
#include <vector>
#include <iostream>
#include <functional>
#include "engine/Entity.hpp"

namespace ecs {

	enum entityType {
		PLAYER, POWERUP, BOMB, WALL, U_WALL, FLAMME,
	};

	class world {
	public:
		world() = default;

		~world() = default;

		entityId createEntity(entityType type);
		void destroyEntity(entityId);
		void _spawnEntitiesFromMap(std::vector<std::string> &&gameMap);
		void _spawnWall(entityType type, size_t posX, size_t posY);
		void _spawnPlayer(size_t posX, size_t posY);
		bool addComponent(entityId id, Position pos);
		bool addComponent(entityId id, Character chara);
		bool addComponent(entityId id, Explosion exp);
		bool addComponent(entityId id, Collectible col);
		bool addComponent(entityId id, Velocity vel);
		bool addComponent(entityId id, Input in);
		bool addComponent(entityId id, AiInput in);
		bool addComponent(entityId id, Destructible des);
		bool addComponent(entityId id, Graphic gfx);
		void drawEntities();

	private:
		entityId curId = 0;
		std::unordered_map<entityId, Entity> _world;
	};
}

#endif //CPP_INDIE_STUDIO_WORLD_HPP