/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ScenesManager
*/

#include <iostream>
#include "scenes/ScenesManager.hpp"
#include "menu/Launch.hpp"
#include "menu/Settings.hpp"

std::unique_ptr<ids::IScene> ids::ScenesManager::makeScene(IScene::sceneId sceneId, gfx::Renderer *renderer)
{
	switch (sceneId) {
	case IScene::MENU:
		return std::make_unique<ids::menu::Launch>(renderer);
	case IScene::SETTINGS:
		std::cout << "renderer in makeScene " << renderer << std::endl;
		return std::make_unique<ids::menu::Settings>(renderer);
	default:
		throw std::runtime_error("Cannot instantiate scene of this type");
	}
}
