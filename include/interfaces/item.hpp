/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Items interface
*/

#pragma once

namespace ids {

	class IItem {
		public:

			enum Powerup {
				SPEED,
				BOMB,
			};

			IItem();
			virtual ~IItem() noexcept = default;
	};

}
