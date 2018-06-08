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
#include "common/Music.hpp"

namespace ids {
	class ScenesManager {
	public:
		explicit ScenesManager(gfx::Renderer *renderer, Music *music);

		std::unique_ptr<ids::IScene> makeScene(IScene::sceneId sceneId);

	private:
		gfx::Renderer *_renderer;
		Music *_music;
	};
}
