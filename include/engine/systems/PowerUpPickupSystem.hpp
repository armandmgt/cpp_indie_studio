/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PowerUpPickupSystem
*/

#pragma once

#include "world/World.hpp"
#include "Systems.hpp"

namespace ecs {
	class PowerUpPickupSystem : public System {
		public:
		PowerUpPickupSystem(const entityVector &allEntities, std::shared_ptr<ecs::World> world);

		void update(double delta) override;

		private:
		bool _pickedUp(Position &playerPos, Entity *powerUp);

		std::shared_ptr<World> _world;
	};
}
