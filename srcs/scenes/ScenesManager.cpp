/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ScenesManager
*/

#include "scenes/GameScene.hpp"
#include "scenes/ScenesManager.hpp"
#include "menu/Launch.hpp"
#include "menu/Settings.hpp"

ids::ScenesManager::ScenesManager(std::shared_ptr<gfx::Renderer> &&renderer) : _renderer{renderer}
{
}

std::unique_ptr<ids::IScene> ids::ScenesManager::makeScene(IScene::sceneId sceneId)
{
	//TODO: change all these .lock().get() by giving weak_ptr to AMenu and GameScene
	switch (sceneId) {
	case IScene::MENU:
		return std::make_unique<ids::menu::Launch>(_renderer);
	case IScene::SETTINGS:
		return std::make_unique<ids::menu::Settings>(_renderer);
	case IScene::GAME:
		return std::make_unique<ids::GameScene>(_renderer);
	default:
		throw std::runtime_error("Cannot instantiate scene of this type");
	}
}
