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
	enum CellType {
		EMPTY, WALL, BOX, BOMB, FLAME
	};

	class PlayerAI {
		public:
		PlayerAI(size_t _id, std::shared_ptr<ecs::World> _world, vec2d<std::size_t> _mapSize);
		~PlayerAI() = default;

		evt::eventType computeAction();

		private:
		std::size_t _id;
		std::shared_ptr<ecs::World> _world;

		std::vector<ecs::Entity *> _allEntities;
		std::vector<ecs::Entity *> _players;
		ecs::Entity * _myself;
		std::vector<ecs::Entity *> _bombs;
		std::vector<std::vector<CellType>> _map;

		std::list<evt::eventAction> _road;
		std::array<evt::eventAction, 4> _directions;

		void _constructTypesMap();
		void _updateMap();
		void _findCellType(const ecs::Entity *entity);
		void _printMap();

		bool _willDie(const vec2d<float> &pos);
		evt::eventAction _findSafePlace(vec2d<float> &pos);
		bool _isSafeRoad(std::list<evt::eventAction> road);

		void _findSaferCell(vec2d<float> &pos, std::map<evt::eventAction, size_t> &pathsLengths,
			std::list<vec2d<float>> &visited
		);
		void _checkCell(vec2d<float> pos, std::map<evt::eventAction, size_t> &pathsLengths,
			std::list<vec2d<float>> &visited, evt::eventAction dir
		);
	};
}
