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
#include "gfx/Renderer.hpp"
#include "map/Map.hpp"

namespace ecs {

	enum entityType {
		PLAYER, POWERUP, BOMB, WALL, U_WALL, FLAMME,
	};

	class world {
	public:
		explicit world(gfx::Renderer &renderer);
		~world() = default;

		Entity &createEntity();
		void destroyEntity(entityId);
		void _spawnEntitiesFromMap(std::vector<std::string> &&gameMap);
		void _spawnUWall(long posX, long posY);
		void _spawnWall(ActionTarget type, long posX, long posY);
		void _spawnBWall(long posX, long posY);
		void _spawnPlayer(long posX, long posY);

		Entity &getEntity(entityId id);
		void debug();

		void createGround(size_t xSize, size_t zSize, irr::core::stringw const &assetPath);
		void drawEntities();
		void systemSpawnBomb(entityId);
		void systemMove(entityId) noexcept;
		void systemSpawnCollectibleFromBox(entityId) noexcept;
		void systemPickupItem(entityId, entityId) noexcept;
		void systemParseInput(const entityId pId) noexcept;

	public:
		std::vector<Entity> _world;

	private:
		entityId curId;
		gfx::Renderer &renderer;
		vec3d<float> sizeGround;
		irr::core::stringw _queryMeshFromActionTarget(ActionTarget) const;
	};
}

#endif //CPP_INDIE_STUDIO_WORLD_HPP
