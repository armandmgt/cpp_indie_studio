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
		explicit ExplosionSystem(std::vector<Entity> *);

		void update(double) override;
	};
}
