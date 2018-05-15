/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Player interface
*/

#pragma once

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
	};
}
