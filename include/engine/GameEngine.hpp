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
#include <interfaces/item.hpp>
#include <interfaces/player.hpp>
#include <interfaces/object.hpp>

namespace ids {

	class GameEngine {
		public:
			GameEngine();
			~GameEngine() noexcept = default;

			std::vector<IPlayer> getPlayers() const noexcept { return this->_players; }
			std::vector<IItem> getItems() const noexcept { return this->_items; }
			std::vector<IObject> getObjects() const noexcept { return this->_objects; }

		private:

			void _spawnPlayer(vec2d<float>, IPlayer::Color);
			void _spawnItem(vec2d<float>, IItem::Powerup);
			void _spawnObject(vec2d<float>, IObject::Type);

			std::vector<IPlayer> _players;
			std::vector<IItem> _items;
			std::vector<IObject> _objects;
	};

}
