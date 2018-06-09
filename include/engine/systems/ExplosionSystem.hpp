/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ExplosionSystem
*/

#pragma once

#include "Systems.hpp"

namespace ecs {
	class ExplosionSystem : public System {
	public:
		explicit ExplosionSystem(std::vector<Entity> *, gfx::Renderer *);

		void update(double) override;
	};
}
