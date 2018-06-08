/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** gamescene
*/

#pragma once

#include <memory>
#include <list>
#include "IScene.hpp"
#include "gfx/Renderer.hpp"
#include "world/World.hpp"
#include "engine/systems/Systems.hpp"

namespace ids {
	class GameScene : public IScene {
		public:
			explicit GameScene(gfx::Renderer *);
			~GameScene() noexcept final = default;

			sceneId run() final;

		private:
			void _initSystem();

		private:
			std::unique_ptr<ecs::World> _world;
			gfx::Renderer *_renderer;
			evt::MyEventReceiver &_event;
			std::list<std::unique_ptr<ecs::System>> _systemList{};
	};
}
