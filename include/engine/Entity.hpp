/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Entities
*/
#ifndef CPP_INDIE_STUDIO_ENTITIES_HPP
#define CPP_INDIE_STUDIO_ENTITIES_HPP

#include <bitset>

namespace ecs {

	using entityId = long;

	class Entity {
	public:
		static std::size_t const bitSize = 5;

		explicit Entity(std::bitset<bitSize> bitset) : id(0),
							       bit(bitset)
		{};
		entityId id;
		std::bitset<bitSize> bit;
	};
}

#endif //CPP_INDIE_STUDIO_ENTITIES_HPP
