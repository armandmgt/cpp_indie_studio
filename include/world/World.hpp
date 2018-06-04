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
		world(gfx::Renderer &renderer);
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

		bool addComponent(entityId id, Position pos) noexcept;
		bool addComponent(entityId id, Character chara) noexcept;
		bool addComponent(entityId id, Explosion exp) noexcept;
		bool addComponent(entityId id, Collectible col) noexcept;
		bool addComponent(entityId id, Velocity vel) noexcept;
		bool addComponent(entityId id, Input in) noexcept;
		bool addComponent(entityId id, AiInput in) noexcept;
		bool addComponent(entityId id, Destructible des) noexcept;
		bool addComponent(entityId id, Graphic gfx) noexcept;
		bool addComponent(entityId id, Orientation orientation) noexcept;

		Entity &getEntity(const entityId id);
		Orientation &getOrientation(const entityId id);
		Position &getPosition(const entityId id);
		Character &getCharacter(const entityId id);
		Explosion &getExplosion(const entityId id);
		Collectible &getCollectible(const entityId id);
		Velocity &getVelocity(const entityId id);
		Input &getInput(const entityId id);
		AiInput &getAiInput(const entityId id);
		Destructible &getDestructible(const entityId id);
		Graphic &getGraphic(const entityId id);
		void debug();
		void drawEntities();

		void createGround(size_t xSize, size_t zSize, irr::core::stringw const &assetPath);

	private:
		entityId curId;
		gfx::Renderer &renderer;
		std::unordered_map<entityId, Entity> _world;
	};
}

#endif //CPP_INDIE_STUDIO_WORLD_HPP
