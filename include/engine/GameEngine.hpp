/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Game Engine
*/

#pragma once

#include <string>
#include <vector>

#include <common/vec.hpp>
#include "entities/Player.hpp"
#include "entities/Item.hpp"
#include "entities/Object.hpp"
//#include "entities/Item.hpp"
//#include "entities/Object.hpp"

namespace ids {

	class GameEngine {
		public:
			GameEngine();
			~GameEngine() noexcept = default;

			std::vector<Player> getPlayers() const noexcept { return this->_players; }
			std::vector<Item> getItems() const noexcept { return this->_items; }
			std::vector<Object> getObjects() const noexcept { return this->_objects; }

		private:

			void _spawnPlayer(vec2d<float>, Player::Color);
			void _spawnItem(vec2d<float>, Item::Powerup);
			void _spawnObject(vec2d<float>, Object::Type);

			std::vector<Player> _players;
			std::vector<Item> _items;
			std::vector<Object> _objects;
	};

}
