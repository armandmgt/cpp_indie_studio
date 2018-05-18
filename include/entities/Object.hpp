/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Object
*/

#pragma once

#include "interfaces/IObject.hpp"

namespace ids {

	class Object : public IObject {
		public:
			Object();
			~Object() noexcept = default;
	};

}
