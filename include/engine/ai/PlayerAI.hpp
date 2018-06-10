/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PlayerAI
*/

#pragma once

#include <list>
#include "world/World.hpp"
#include "event/EventReceiver.hpp"

namespace ids {
	enum cellType {
		EMPTY, WALL, BOX, BOMB, FLAME
	};

	struct PathTree {
		PathTree(evt::eventAction path, size_t length) : path(path), length(length)
		{
		}

		evt::eventAction path;
		std::size_t length;
		std::array<std::unique_ptr<PathTree>, 4> leafs{};
	};

	class PlayerAI {
		public:
		PlayerAI(size_t _id, std::shared_ptr<ecs::World> _world, vec2d<std::size_t> _mapSize);

		~PlayerAI() = default;

		evt::Event computeAction();

		private:
		std::size_t _id;
		std::shared_ptr<ecs::World> _world;

		std::vector<ecs::Entity *> _allEntities;
		std::vector<ecs::Entity *> _players;
		ecs::Entity *_myself;
		std::vector<ecs::Entity *> _bombs;
		std::vector<std::vector<cellType>> _map;

		std::list<evt::eventAction> _road;
		std::array<evt::eventAction, 4> _directions;

		void _constructTypesMap();
		void _updateMap();
		void _findCellType(const ecs::Entity *entity);

		bool _willDie(const vec2d<float> &pos);
		evt::eventAction _findSafePlace(vec2d<float> &pos);
		bool _isSafeRoad(std::list<evt::eventAction> road);

		void _findSaferCell(vec2d<float> &pos, std::unique_ptr<PathTree> &pathsLengths,
			std::list<vec2d<float>> &visited
		);
	};
}
