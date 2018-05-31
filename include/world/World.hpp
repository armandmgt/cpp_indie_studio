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
#include <string>
#include "engine/Entity.hpp"

namespace ecs {

	enum entityType {
		PLAYER, POWERUP, BOMB, WALL, FLAMME,
	};

	class world {
	public:
		world() = default;
		~world() = default;

		entityId createEntity(entityType type);
		void destroyEntity(entityId id);

	private:
		std::unordered_map<entityId, Entity> _world;

		void _spawnEntitiesFromMap(std::vector<std::string>&&);
		void _spawnWall(size_t, size_t);
	};
}

#endif //CPP_INDIE_STUDIO_WORLD_HPP
