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
		static std::size_t bitsize = 5;
		entityId id;
		std::bitset<bitsize> bit;
	};
}

#endif //CPP_INDIE_STUDIO_ENTITIES_HPP
