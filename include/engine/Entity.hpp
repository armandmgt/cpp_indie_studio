/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Entities
*/
#ifndef CPP_INDIE_STUDIO_ENTITIES_HPP
#define CPP_INDIE_STUDIO_ENTITIES_HPP

#include <bitset>
#include <vector>
#include "Components.hpp"

namespace ecs {

	using entityId = unsigned long;

	class Entity {
	public:
		static std::size_t const bitSize = 10;

		explicit Entity(std::vector<int> &bitset) : id(0)
		{
			for (auto &b : bitset) {
				bit[b] = true;
			}
		};
		template<class T>
		T &getComponent() { return componentArray[T::getType()]; }
		template <typename T, typename... Args> void addComponent(Args&&... args) {
			componentArray[T::getType()] = T{std::forward<Args>(args)...};
		}
		entityId id;
		std::bitset<bitSize> bit;
		std::vector<Component> componentArray;
	};
}

#endif //CPP_INDIE_STUDIO_ENTITIES_HPP
