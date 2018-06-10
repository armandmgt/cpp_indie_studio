/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Systems
*/

#pragma once

#include <algorithm>
#include "gfx/Renderer.hpp"
#include "engine/Entity.hpp"

namespace ecs {
	class System {
	public:
		explicit System(std::shared_ptr<std::vector<Entity>> allEntities) : _allEntities(allEntities)
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
			auto typesArr = {types...};
			return std::all_of(std::begin(typesArr), std::end(typesArr), [&entity](comp type) {
				return entity.bit[type];
			});
		}

	protected:
		std::shared_ptr<std::vector<Entity>> _allEntities;
	private:
		std::vector<Entity *> _entities;
	};
};
