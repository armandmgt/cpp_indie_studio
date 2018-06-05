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

		Entity &createEntity(entityType type);
		void destroyEntity(entityId);
		void _spawnEntitiesFromMap(std::vector<std::string> &&gameMap);
		void _spawnUWall(long posX, long posY);
		void _spawnWall(ActionTarget type, long posX, long posY);
		void _spawnBWall(long posX, long posY);
		void _spawnPlayer(long posX, long posY);

		bool addComponent(Entity &ent, Position pos) noexcept;
		bool addComponent(Entity &ent, Character chara) noexcept;
		bool addComponent(Entity &ent, Explosion exp) noexcept;
		bool addComponent(Entity &ent, Collectible col) noexcept;
		bool addComponent(Entity &ent, Velocity vel) noexcept;
		bool addComponent(Entity &ent, Input in) noexcept;
		bool addComponent(Entity &ent, AiInput in) noexcept;
		bool addComponent(Entity &ent, Destructible des) noexcept;
		bool addComponent(Entity &ent, Graphic gfx) noexcept;
		bool addComponent(Entity &ent, Orientation orientation) noexcept;

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
		void systemSpawnBomb(const entityId) noexcept;
		void systemMove(const entityId) noexcept;
		void systemSpawnCollectibleFromBox(const entityId) noexcept;
		void systemPickupItem(const entityId, const entityId) noexcept;

	private:
		entityId curId;
		gfx::Renderer &renderer;
		vec3d<float> sizeGround;
		std::string _queryMeshFromActionTarget(const ActionTarget) const;
		std::vector<Entity> _world;
	};
}

#endif //CPP_INDIE_STUDIO_WORLD_HPP
