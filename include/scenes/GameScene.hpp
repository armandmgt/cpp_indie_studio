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
#include "engine/ai/PlayerAI.hpp"

namespace ids {
	class GameScene : public IScene {
		public:
			explicit GameScene(std::shared_ptr<gfx::Renderer>);
			~GameScene() noexcept final;

			sceneId run() final;

		private:
			bool _isWin();
			void _initSystem();

		private:
			std::shared_ptr<ecs::World> _world;
			std::shared_ptr<gfx::Renderer> _renderer;
			evt::MyEventReceiver &_event;
			std::list<std::unique_ptr<ecs::System>> _systemList{};
			PlayerAI _ai1;
			PlayerAI _ai2;

	};
}
