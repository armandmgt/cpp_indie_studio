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
		std::unique_ptr<ids::IScene> makeScene(IScene::sceneId sceneId, gfx::Renderer *renderer);
	};
}
