/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Entities
*/
#ifndef CPP_INDIE_STUDIO_ENTITIES_HPP
#define CPP_INDIE_STUDIO_ENTITIES_HPP

#include <bitset>
#include "Components.hpp"

namespace ecs {

	using entityId = long;

	class Entity {
	public:
		static std::size_t const bitSize = 8;

		explicit Entity(std::bitset<bitSize> bitset) : id(0),
							       bit(bitset)
		{};
		entityId id;
		std::bitset<bitSize> bit;

		Character cCharacter{};
		Explosion cExplosion{};
		Collectible cCollectible{};
		Velocity cVelocity{};
		Position cPosition{};
		Input cInput{};
		AiInput cAiInput{};
		Destructible cDestructible{};
	};
}

#endif //CPP_INDIE_STUDIO_ENTITIES_HPP
