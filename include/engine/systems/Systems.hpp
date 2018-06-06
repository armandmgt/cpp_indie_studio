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
			_entities.clear();
			for (auto &e : *_allEntities) {
				if (passFilter<Types...>(e, types...))
					_entities.push_back(&e);
			}
			return _entities;
		}

		template<class... Types>
		bool passFilter(Entity &entity, Types... types) {
			for (comp type : {types...}) {
				if (!entity.bit[type])
					return false;
			}
			return true;
		}

	private:
		std::vector<Entity> *_allEntities;
		std::vector<Entity *> _entities;
	};
};
