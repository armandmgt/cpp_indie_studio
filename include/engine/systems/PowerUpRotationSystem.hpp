/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PowerUpRotationSystem
*/

#pragma once

#include "Systems.hpp"

namespace ecs {
	class PowerUpRotationSystem : public System {
		public:
		PowerUpRotationSystem(const entityVector &allEntities, std::shared_ptr<gfx::Renderer> renderer);

		void update(double delta) override;

		private:
		std::shared_ptr<gfx::Renderer> _renderer;
	};
}
