/*
** EPITECH PROJECT, 2017
** cpp_indie_studio
** File description:
** Created by armandmgt,
*/

#include "engine/GameContainer.hpp"

ids::GameContainer::GameContainer() : _renderer{std::make_shared<gfx::Renderer>()},
	_music{std::make_shared<ids::Music>()}, _scenesManager{_renderer, _music},
	_ecs{std::make_shared<ecs::World>(_renderer)}
{
}

void ids::GameContainer::start()
{
	IScene::sceneId sceneId = IScene::MENU;
	std::unique_ptr<IScene> gameHolder;

	while (sceneId != IScene::QUIT) {
		std::unique_ptr<IScene> scene;
		if (sceneId == IScene::GAME && gameHolder)
			scene = std::move(gameHolder);
		else
			scene = _scenesManager.makeScene(sceneId);
		if ((sceneId = scene->run()) == IScene::QUIT)
			return;
		if (sceneId == IScene::PAUSE)
			gameHolder = std::move(scene);
	}
}
