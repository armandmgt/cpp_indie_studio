/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** gamescene
*/

#include "engine/ai/PlayerAI.hpp"
#include "GameScene.hpp"

ids::GameScene::GameScene(gfx::Renderer *r)
		: _world{std::make_shared<ecs::World>(r)}, _renderer{r}, _event{r->getEventReceiver()} {
	Map map(20, 20);

	map.initMap(20);
	map.printMap();
	_world->createGround(20, 20, "../assets/meshs/ground.obj");
	_world->spawnEntitiesFromMap(std::move(map.getMap()));
	auto &e = _world->createEntity();
	e.addComponent<ecs::Position>(2.1f, 1.2f);
	e.addComponent<ecs::Explosion>(3LU, 5LU);
	e.addComponent<ecs::Graphic>(_renderer->createElem("../assets/meshs/bomb.obj"));
}

ids::IScene::sceneId ids::GameScene::run() {
	_renderer->setCameraFPS();
	_world->drawEntities();
	PlayerAI ai1{0LU, _world, {20, 20}};
	auto e = ai1.computeAction();
	std::cout << "Best AI in the world computed: " << e.action << " and " << e.key << std::endl;
	while (_renderer->isRunning() && !_event.isKeyDown(irr::KEY_ESCAPE)) {
		_renderer->render();
	}
	return MENU;
}