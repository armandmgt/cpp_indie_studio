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

	template<class T>
	vec2d<T> toIntegerPos(const vec2d<float> &pos) {
		return {static_cast<T>(std::lround(pos.x)),
			static_cast<T>(std::lround(pos.y))};
	}

	template<class T>
	vec2d<T> toIntegerPos(float x, float y) {
		return {static_cast<T>(std::lround(x)),
			static_cast<T>(std::lround(y))};
	}

	class World {
	public:
		explicit World(gfx::Renderer *renderer);
		~World() = default;

		Entity &createEntity();
		void spawnEntitiesFromMap(std::vector<std::string> &&gameMap);
		void spawnUWall(long posX, long posY);
		void spawnWall(ActionTarget type, long posX, long posY);
		void spawnBWall(long posX, long posY);
		void spawnPlayer(long posX, long posY);
		void spawnFlames(Position, int);

		void createGround(size_t xSize, size_t zSize, irr::core::stringw const &assetPath);
		void drawEntities();
		void destroyEntity(std::size_t &id);
		void spawnBombSystem(Entity *);
		void spawnCollectibleFromBoxSystem(Entity *) noexcept;

		entityVector getEntities();

	public:
		entityVector entities;

	private:
		std::size_t _currId = 0;
		gfx::Renderer *renderer;
		vec3d<float> sizeGround;
		irr::core::stringw _queryMeshFromActionTarget(ActionTarget) const;
	};
}

#endif //CPP_INDIE_STUDIO_WORLD_HPP
