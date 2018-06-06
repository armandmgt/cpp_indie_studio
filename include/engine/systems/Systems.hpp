/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Systems
*/

#pragma once

#include "engine/Entity.hpp"

namespace ecs {
	class System {
	public:
		explicit System(std::vector<Entity> *allEntities) : _allEntities(allEntities)
		{};
		virtual void update(double delta) = 0;

		template<class... Types>
		std::vector<Entity *> &getEntities(Types... types) {
			for (auto &e : *_allEntities) {
				if (passFilter<Types...>(e, types...))
					_entities.push_back(&e);
			}
			return _entities;
		}

		template<class... Types>
		bool passFilter(Entity &entity, Types... types) {
			for (auto type : {types...}) {
				std::cout << "checking for type " << type << std::endl;
				if (!entity.bit[type]) {
					std::cout << "false" << std::endl;
					return false;
				}
			}
			std::cout << "true" << std::endl;
			return true;
		}

	private:
		std::vector<Entity> *_allEntities;
		std::vector<Entity *> _entities;
	};
};
