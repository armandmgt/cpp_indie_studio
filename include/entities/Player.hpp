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
			Player(vec2d<float>, Color, std::string &);
			~Player() noexcept = default;

			Color getColor() const noexcept override;
			std::string &getName() const noexcept override;
			vec2d<float> getPosition() const noexcept override;
			float getSpeed() const noexcept override;
			Directions getDirection() const noexcept override;

			vec2d<float> walk(const Directions) override;
			void putObject(IObject) override;
			void taunt() const override;
	};

}
