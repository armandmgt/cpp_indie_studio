/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ExplosionSystem
*/

#pragma once

#include "world/World.hpp"
#include "Systems.hpp"

namespace ecs {
	class ExplosionSystem : public System {
	public:
		explicit ExplosionSystem(entityVector, std::shared_ptr<gfx::Renderer>,
					 std::shared_ptr<ecs::World> world);

		void update(double) override;

	private:
		std::shared_ptr<gfx::Renderer> _renderer;
		std::shared_ptr<ecs::World> _world;
	};
}
