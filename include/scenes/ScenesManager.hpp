/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ScenesManager
*/

#pragma once

#include <memory>
#include "gfx/Renderer.hpp"
#include "scenes/IScene.hpp"

namespace ids {
	class ScenesManager {
	public:
		explicit ScenesManager(std::shared_ptr<gfx::Renderer> &&);

		std::unique_ptr<ids::IScene> makeScene(IScene::sceneId sceneId);

	private:
//		gfx::Renderer *_renderer;
		std::shared_ptr<gfx::Renderer> _renderer;
	};
}
