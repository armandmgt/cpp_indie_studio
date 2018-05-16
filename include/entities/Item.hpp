/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Item
*/

#pragma once

#include "interfaces/IItem.hpp"

namespace ids {

	class Item : public IItem {
		public:
			Item();
			~Item() noexcept = default;
	};

}
