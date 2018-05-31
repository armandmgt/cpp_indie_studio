/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** world
*/
#ifndef CPP_INDIE_STUDIO_WORLD_HPP
#define CPP_INDIE_STUDIO_WORLD_HPP

#include <unordered_map>
#include "engine/Entity.hpp"

namespace ecs {

	enum entityType {
		PLAYER, POWERUP, BOMB, WALL, FLAMME,
	};

	class world {
	public:
		world() = default;
		~world() = default;

		template<typename ... Ts>
		entityId world::createEntity(entityType type, Ts components) {
			static std::unordered_map<entityType, std::bitset<Entity::bitSize>> map {
				{PLAYER, COMP_POSITION | COMP_VELOCITY | COMP_CHARACTER | COMP_DESTRUCTIBLE},
				{POWERUP, COMP_POSITION | COMP_COLLECTIBLE},
				{BOMB, COMP_VELOCITY | COMP_EXPLOSION},
				{WALL, COMP_POSITION | COMP_DESTRUCTIBLE},
				{FLAMME, COMP_POSITION}
			};

			auto c_types = map[type];
			Entity newEntity(c_types);
			if ((c_types & COMP_CHARACTER) == COMP_CHARACTER) {
				newEntity.cCharacter = components;
				std::forward(components);
			}
			if ((c_types & COMP_EXPLOSION) == COMP_EXPLOSION) {
				newEntity.cExplosion = components;
				std::forward(components);
			}
²