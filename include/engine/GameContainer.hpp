/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** GameContainer
*/

#pragma once

#include <stack>
#include <irrlicht/irrlicht.h>
#include "gfx/Renderer.hpp"
#include "world/World.hpp"
#include "event/Event.hpp"
#include "scenes/ScenesManager.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

namespace ids {
	class GameContainer {
	public:
		GameContainer();
		GameContainer(GameContainer &) = delete;
		GameContainer &operator=(GameContainer &) = delete;

		void start();

	private:
		ScenesManager _scenesManager;
		std::stack<std::unique_ptr<IScene>> _scenes;
		gfx::Renderer _renderer;
		ecs::World _ecs;
	};
}
