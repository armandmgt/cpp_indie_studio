/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** DisparitionFlammeSystem
*/

#pragma once

#include <world/World.hpp>
#include "Systems.hpp"

namespace ecs {
	class DisparitionFlammeSystem : public System {
	public:
		explicit DisparitionFlammeSystem(std::shared_ptr<std::vector<Entity>> , gfx::Renderer *,
		std::shared_ptr<ecs::World>
		        world);

		void update(double) override;

	private:
		gfx::Renderer *_renderer;
		std::shared_ptr<ecs::World> _world;
	};
}
