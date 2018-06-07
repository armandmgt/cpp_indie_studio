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
			GameScene(gfx::Renderer *);
			~GameScene() noexcept final = default;

			std::unique_ptr<ecs::World> &getWorld();
			sceneId run() final override;

		private:
			gfx::Renderer *_rend;
			std::unique_ptr<ecs::World> _world;
	};
}
