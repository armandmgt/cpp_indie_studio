/*
** EPITECH PROJECT, 2017
** cpp_indie_studio
** File description:
** Created by armandmgt,
*/

#include "engine/GameContainer.hpp"

//TODO: remove this .get() and make ecs::World take a weak_ptr
ids::GameContainer::GameContainer() : _scenesManager{std::make_shared<gfx::Renderer>()}, _renderer{}, _ecs{&_renderer} {
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
