/*
** EPITECH PROJECT, 2017
** cpp_indie_studio
** File description:
** Created by armandmgt,
*/

#include "engine/GameContainer.hpp"

ids::GameContainer::GameContainer() : _scenes{}, _renderer{}, _ecs{&_renderer}
{
	_scenes.push(_scenesManager.makeScene(IScene::MENU, &_renderer));
}

void ids::GameContainer::start()
{
	while (!_scenes.empty()) {
		IScene::sceneId rc;
		std::unique_ptr<IScene> &actualScene = _scenes.top();
		if ((rc = actualScene->run()) == IScene::QUIT)
			return;
		else if (rc == IScene::BACK)
			_scenes.pop();
		else
			_scenes.push(_scenesManager.makeScene(rc, &_renderer));
	}
}
