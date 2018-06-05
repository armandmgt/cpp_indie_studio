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

		entityId createEntity(entityType type);
		void destroyEntity(entityId);
		void _spawnEntitiesFromMap(std::vector<std::string> &&gameMap);
		void _spawnUWall(long posX, long posY);
		void _spawnWall(ActionTarget type, long posX, long posY);
		void _spawnBWall(long posX, long posY);
		void _spawnPlayer(long posX, long posY);

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

		Entity &getEntity(entityId id);
		Orientation &getOrientation(entityId id);
		Position &getPosition(entityId id);
		Character &getCharacter(entityId id);
		Explosion &getExplosion(entityId id);
		Collectible &getCollectible(entityId id);
		Velocity &getVelocity(entityId id);
		Input &getInput(entityId id);
		AiInput &getAiInput(entityId id);
		Destructible &getDestructible(entityId id);
		Graphic &getGraphic(entityId id);
		void debug();

		void createGround(size_t xSize, size_t zSize, irr::core::stringw const &assetPath);
		void drawEntities();
		void systemSpawnBomb(entityId);
		void systemMove(entityId);
		void systemSpawnCollectibleFromBox(entityId);
		std::string queryMeshFromActionTarget(ActionTarget) const;

	private:
		entityId curId;
		gfx::Renderer &renderer;
		vec3d<float> sizeGround;
		std::vector<Entity> _world;
	};
}

#endif //CPP_INDIE_STUDIO_WORLD_HPP
