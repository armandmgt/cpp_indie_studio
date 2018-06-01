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
		bool addPosition(entityId id, Position pos);
		bool addCharacter(entityId id, Character chara);
		bool addExplosion(entityId id, Explosion exp);
		bool addCollectible(entityId id, Collectible col);
		bool addVelocity(entityId id, Velocity vel);
		bool addInput(entityId id, Input in);
		bool addAiInput(entityId id, AiInput in);
		bool addDestructible(entityId id, Destructible des);

	private:
		entityId curId = 0;
		std::unordered_map<entityId, Entity> _world;
	};
}

#endif //CPP_INDIE_STUDIO_WORLD_HPP