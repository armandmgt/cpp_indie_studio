/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Game Engine
*/

#pragma once

#include <string>
#include <vector>

#include <interfaces/item.hpp>
#include <interfaces/player.hpp>
#include <interfaces/object.hpp>

namespace ids {

	class GameEngine {
		public:
			GameEngine();
			~GameEngine() noexcept = default;

			std::vector<IPlayer> getPlayers() { return this->_players; }
			std::vector<IItem> getItems() { return this->_items; }
			std::vector<IObject> getObjects() { return this->_objects; }

		private:

			void _spawnPlayer(std::pair<float, float>, IPlayer::Color);
			void _spawnItem(std::pair<float, float>, IItem::Powerup);
			void _spawnObject(std::pair<float, float>, IObject::Type);

			std::vector<IPlayer> _players;
			std::vector<IItem> _items;
			std::vector<IObject> _objects;
	};

}
