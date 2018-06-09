/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MovementSystem
*/

#pragma once

#include "world/World.hpp"
#include "Systems.hpp"

namespace ecs {
	class PutBombSystem : public System {
	public:
		explicit PutBombSystem(std::vector<Entity> *allEntities, std::shared_ptr<ecs::World> world);

		void update(double delta) override;
	private:
		std::shared_ptr<ecs::World> _world;
	};
};