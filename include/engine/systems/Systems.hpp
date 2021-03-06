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
	using entityVector = std::shared_ptr<std::vector<std::unique_ptr<Entity>>>;
	
	class System {
	public:
		explicit System(entityVector allEntities) : _allEntities(allEntities)
		{};
		virtual void update(double delta) = 0;

		template<class... Types>
		std::vector<Entity *> getEntities(Types... types) {
			std::vector<Entity *> _entities;
			for (const auto &e : *_allEntities) {
				if (passFilter<Types...>(e, types...))
					_entities.push_back(e.get());
			}
			return _entities;
		}

		template<class... Types>
		bool passFilter(const std::unique_ptr<Entity> &entity, Types... types) {
			auto typesArr = {types...};
			return std::all_of(std::begin(typesArr), std::end(typesArr), [&entity](comp type) {
				return entity->bit[type];
			});
		}

	protected:
		entityVector _allEntities;
	};
};
