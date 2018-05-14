/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Object interface
*/

#pragma once

namespace ids {

	class IObject {
		public:

			enum Type {
				BOMB,
				FLAME,
			};

			IObject();
			virtual ~IObject() noexcept = default;
	};

}
