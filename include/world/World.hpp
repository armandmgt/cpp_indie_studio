/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** World
*/

#ifndef CPP_INDIE_STUDIO_WORLD_HPP
#define CPP_INDIE_STUDIO_WORLD_HPP

#include <vector>
#include "engine/systems/Systems.hpp"
#include "gfx/Renderer.hpp"
#include "map/Map.hpp"

namespace ecs {

	using entityVector = std::shared_ptr<std::vector<std::unique_ptr<Entity>>>;

	class World {
	public:
		explicit World(std::shared_ptr<gfx::Renderer> renderer);
		~World() = default;

		Entity &createEntity();
		void spawnEntitiesFromMap(std::vector<std::string> &&gameMap);
		void spawnUWall(long posX, long posY);
		void spawnWall(ActionTarget type, long posX, long posY);
		void spawnBWall(long posX, long posY);
		void spawnPlayer(long posX, long posY);
		void spawnFlames(Position, int);
		void spawnFlameAtPosition(float x, float y);

		void createGround(size_t xSize, size_t zSize, irr::core::stringw const &assetPath);
		void drawEntities();
		void destroyEntity(std::size_t &id);
		void spawnBombSystem(Entity *);
		void spawnCollectibleFromBox(Entity *) noexcept;
		bool isValidPosition(float x, float y);

		entityVector getEntities();

	public:
		entityVector entities;

	private:
		vec3d<float> _sizeGround;
		std::shared_ptr<gfx::Renderer> _renderer;
		irr::core::stringw _queryMeshFromActionTarget(ActionTarget) const;
	};
}

#endif //CPP_INDIE_STUDIO_WORLD_HPP
