/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PlayerRotationSystem
*/

#pragma once

#include "Systems.hpp"

namespace ecs {
	class PlayerRotationSystem : public System {
		public:
		PlayerRotationSystem(entityVector, std::shared_ptr<gfx::Renderer> renderer);

		void update(double delta) override;

		private:
		std::shared_ptr<gfx::Renderer> _renderer;
	};
}
