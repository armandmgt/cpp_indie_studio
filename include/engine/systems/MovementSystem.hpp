/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MovementSystem
*/

#pragma once

#include "Systems.hpp"

namespace ecs {
	class MovementSystem : public System {
	public:
		explicit MovementSystem(std::vector<Entity> *, gfx::Renderer *);

		void update(double delta) override;
	};
};