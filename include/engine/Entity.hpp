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
#include <array>
#include "Components.hpp"

namespace ecs {

	using entityId = unsigned long;

	class Entity {
	public:
		Entity(std::size_t entityId) : bit{0}, id(entityId),
					       componentArray{nullptr}
		{};
		Entity(Entity &) = delete;
		Entity &operator=(Entity &) = delete;
		Entity(Entity &&) = default;
		Entity &operator=(Entity &&) = default;

		template<class T>
		T &getComponent() {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			std::cerr << T::type << std::endl;
			if (!bit[T::type])
				throw std::runtime_error("Entity has no T component");
			return static_cast<T&>(*componentArray[T::type]);
		}

		template<class T>
		bool hasComponent() {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			return bit[T::type];
		}

		template <typename T, typename... Args>
		void addComponent(Args&&... args) {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			bit[T::type] = true;
			componentArray[T::type] = std::unique_ptr<T>(new T{std::forward<Args>(args)...});
		}

		template<class T>
		void removeComponent() {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			bit[T::type] = false;
			delete componentArray[T::type];
		}

	public:
		std::bitset<MAX_COMPONENTS> bit;
		std::size_t id;
	private:
		std::array<std::unique_ptr<Component>, MAX_COMPONENTS> componentArray;
	};
}

#endif //CPP_INDIE_STUDIO_ENTITIES_HPP
