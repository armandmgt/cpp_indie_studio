/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Player interface
*/

#pragma once

namespace ids {

	class IPlayer {

		public:
			enum Color {
				WHITE,
				RED,
				BLUE,
				GREEN,
			};

			IPlayer();
			virtual ~IPlayer() noexcept = default;
	};

}
