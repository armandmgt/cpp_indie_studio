/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** gamescene
*/

#include "GameScene.hpp"

ids::GameScene::GameScene(gfx::Renderer *r) : _rend{r} {
	this->_world = std::make_unique<ecs::World>(r);

	Map map(22, 20);
	map.initMap(20);
	map.printMap();
	_world->createGround(22, 20, "../assets/meshs/ground.obj");
	_world->spawnEntitiesFromMap(std::move(map.getMap()));
}

ids::IScene::sceneId ids::GameScene::run() {
	_rend->setCameraFPS();
	_world->drawEntities();
	while (_rend->isRunning() && !_rend->isKeyPressed(irr::KEY_ESCAPE)) {
		_rend->render();
	}
	return MENU;
}

std::unique_ptr<ecs::World> &ids::GameScene::getWorld() {
	return _world;
}
