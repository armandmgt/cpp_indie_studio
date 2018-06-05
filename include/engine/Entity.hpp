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
		template<class T>
		T &getComponent() { return componentArray[T::getType()]; }

		template<class T>
		bool hasComponent() { return bit[T::getType()]; }

		template <typename T, typename... Args>
		void addComponent(Args&&... args) {
			bit[T::getType()] = true;
			componentArray[T::getType()] = T{std::forward<Args>(args)...};
		}

		entityId id;

	private:
		std::bitset<MAX_COMPONENTS> bit;
		std::vector<Component> componentArray;
	};
}

#endif //CPP_INDIE_STUDIO_ENTITIES_HPP
