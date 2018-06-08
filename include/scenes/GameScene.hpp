/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** gamescene
*/

#pragma once

#include <memory>
#include "IScene.hpp"
#include "gfx/Renderer.hpp"
#include "world/World.hpp"

namespace ids {
	class GameScene : public IScene {
		public:
			explicit GameScene(gfx::Renderer *);
			~GameScene() noexcept final = default;

			sceneId run() final;

		private:
			std::unique_ptr<ecs::World> _world;
			gfx::Renderer *_renderer;
	};
}
