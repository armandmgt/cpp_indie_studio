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
		void SystemSpawnBomb(entityId id);
		bool addComponent(entityId id, Position pos);
		bool addComponent(entityId id, Character chara);
		bool addComponent(entityId id, Explosion exp);
		bool addComponent(entityId id, Collectible col);
		bool addComponent(entityId id, Velocity vel);
		bool addComponent(entityId id, Input in);
		bool addComponent(entityId id, AiInput in);
		bool addComponent(entityId id, Destructible des);
		bool addComponent(entityId id, Graphic gfx);

		Entity getEntity(entityId) const;
		Position getPosition(entityId id) const;
		Character getCharacter(entityId id) const;
		Explosion getExplosion(entityId id) const;
		Collectible getCollectible(entityId id) const;
		Velocity getVelocity(entityId id) const;
		Input getInput(entityId id) const;
		AiInput getAiInput(entityId id) const;
		Destructible getDestructible(entityId id) const;
		Graphic getGraphic(entityId id) const;
		void drawEntities();

	private:
		entityId curId = 0;
		std::unordered_map<entityId, Entity> _world;
	};
}

#endif //CPP_INDIE_STUDIO_WORLD_HPP
