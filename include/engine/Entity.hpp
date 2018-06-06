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
		Entity() : bit{}, componentArray{}
		{};

		template<class T>
		T &getComponent() {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			if (!bit[T::getType()])
				throw std::runtime_error("Entity has no T component");
			return static_cast<T&>(*componentArray[T::getType()]);
		}

		template<class T>
		bool hasComponent() {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			return bit[T::getType()];
		}

		template <typename T, typename... Args>
		void addComponent(Args&&... args) {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			bit[T::getType()] = true;
			componentArray[T::getType()] = new T{std::forward<Args>(args)...};
		}

		template<class T>
		void removeComponent() {
			bit[T::getType()] = false;
		}

	private:
		std::bitset<MAX_COMPONENTS> bit;
		std::array<Component*, MAX_COMPONENTS> componentArray;
	};
}

#endif //CPP_INDIE_STUDIO_ENTITIES_HPP
