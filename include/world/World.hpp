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
#include <glob.h>
#include "engine/Entity.hpp"
#include "map/Map.hpp"

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
		void _spawnUWall(long posX, long posY);
		void _spawnWall(mapItem type, long posX, long posY);
		void _spawnBWall(long posX, long posY);
		void _spawnPlayer(long posX, long posY);

		void systemSpawnBomb(entityId);
		void systemMove(entityId);
		void systemSpawnCollectibleFromBox(entityId);

		bool addComponent(entityId id, Position pos);
		bool addComponent(entityId id, Character chara);
		bool addComponent(entityId id, Explosion exp);
		bool addComponent(entityId id, Collectible col);
		bool addComponent(entityId id, Velocity vel);
		bool addComponent(entityId id, Input in);
		bool addComponent(entityId id, AiInput in);
		bool addComponent(entityId id, Destructible des);
		bool addComponent(entityId id, Graphic gfx);

		Entity &getEntity(const entityId);
		Position &getPosition(const entityId id);
		Character &getCharacter(const entityId id);
		Explosion &getExplosion(const entityId id);
		Collectible &getCollectible(const entityId id);
		Velocity &getVelocity(const entityId id);
		Input &getInput(const entityId id);
		AiInput &getAiInput(const entityId id);
		Destructible &getDestructible(const entityId id);
		Graphic &getGraphic(const entityId id);
		void drawEntities();

	private:
		entityId curId = 0;
		std::unordered_map<entityId, Entity> _world;
	};
}

#endif //CPP_INDIE_STUDIO_WORLD_HPP
