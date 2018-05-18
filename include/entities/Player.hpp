/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Player class
*/

#pragma once

#include "interfaces/IPlayer.hpp"
#include "common/vec.hpp"

namespace ids {

	class Player : public IPlayer {
		public:
			Player(vec2d<float>, Color, const std::string &);
			~Player() noexcept = default;

			Color getColor() const noexcept override { return this->_color; };
			std::string getName() const noexcept override { return this->_name; };
			vec2d<float> getPosition() const noexcept override { return this->_position; };
			float getSpeed() const noexcept override { return this->_speed; };
			Directions getDirection() const noexcept override { return this->_direction; };

			vec2d<float> walk(const Directions) override;
			void putObject(IObject) override;
			void taunt() const override;

		private:
			Color _color;
			std::string _name;

			vec2d<float> _position;
			Directions _direction;
			float _speed;
	};

}
