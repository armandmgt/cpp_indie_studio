/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** gamescene
*/

#include "GameScene.hpp"

ids::GameScene::GameScene(gfx::Renderer *r)
		: _world{std::make_unique<ecs::World>(r)}, _renderer{r} {
	Map map(22, 20);

	map.initMap(20);
	map.printMap();
	_world->createGround(22, 20, "../assets/meshs/ground.obj");
	_world->spawnEntitiesFromMap(std::move(map.getMap()));
}

ids::IScene::sceneId ids::GameScene::run() {
	_renderer->setCameraFPS();
	_world->drawEntities();
	while (_renderer->isRunning() && !_renderer->isKeyPressed(irr::KEY_ESCAPE))
		_renderer->render();
	return MENU;
}