/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Player interface
*/

#pragma once

#include <string>

#include "enum/Directions.hpp"
#include "interfaces/IObject.hpp"
#include "common/vec.hpp"

namespace ids {
	class IPlayer {
		public:
			enum Color {
				WHITE,
				RED,
				BLUE,
				GREEN,
			};

			virtual ~IPlayer() noexcept = default;

			virtual Color getColor() const noexcept = 0;
			virtual std::string &getName() const noexcept = 0;
			virtual vec2d<float> getPosition() const noexcept = 0;
			virtual float getSpeed() const noexcept = 0;
			virtual Directions getDirection() const noexcept = 0;

			virtual vec2d<float> walk(const Directions) = 0;
			virtual void putObject(IObject) = 0;
			virtual void taunt() const = 0;
	};
}
