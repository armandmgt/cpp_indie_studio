/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** gamescene
*/

#include "GameScene.hpp"

ids::GameScene::GameScene(std::shared_ptr<gfx::Renderer> r) : _world{std::make_unique<ecs::World>(r)},
	_renderer{r}, _event{r->getEventReceiver()} {
	Map map(21, 20);

	map.initMap(20);
	map.printMap();
	_world->createGround(21, 20, "../assets/meshs/ground.obj");
	_world->spawnEntitiesFromMap(std::move(map.getMap()));
}

ids::IScene::sceneId ids::GameScene::run() {
	_renderer->setCameraFPS();
	_world->drawEntities();
	while (_renderer->isRunning() && !_renderer->getEventReceiver().isKeyDown(irr::KEY_ESCAPE)) {
		_renderer->render();
	}
	return PAUSE;
}