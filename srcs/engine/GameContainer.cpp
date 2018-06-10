/*
** EPITECH PROJECT, 2017
** cpp_indie_studio
** File description:
** Created by armandmgt,
*/

#include "engine/GameContainer.hpp"

ids::GameContainer::GameContainer() : _renderer{}, _music{}, _scenesManager{_renderer, _music}, _ecs{_renderer}
{
}

void ids::GameContainer::start()
{
	IScene::sceneId sceneId = IScene::MENU;

	while (sceneId != IScene::QUIT) {
		std::unique_ptr<IScene> scene{_scenesManager.makeScene(sceneId)};
		if ((sceneId = scene->run()) == IScene::QUIT)
			return;
	}
}
