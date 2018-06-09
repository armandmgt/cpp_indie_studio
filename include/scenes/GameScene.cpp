/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** gamescene
*/

#include <engine/systems/PlayerMovement.hpp>
#include <engine/systems/MovementSystem.hpp>
#include <engine/systems/ParseInputSystem.hpp>
#include "GameScene.hpp"

ids::GameScene::GameScene(gfx::Renderer *r)
		: _world{std::make_unique<ecs::World>(r)}, _renderer{r}, _event{r->getEventReceiver()} {
	Map map(21, 20);

	map.initMap(20);
	map.printMap();
	_world->createGround(21, 20, "../assets/meshs/ground.obj");
	_world->spawnEntitiesFromMap(std::move(map.getMap()));
}

void ids::GameScene::_initSystem()
{
	std::unique_ptr<ecs::PlayerMovement> movPlayerSys = std::make_unique<ecs::PlayerMovement>(&_world->entities);
	std::unique_ptr<ecs::MovementSystem> movSys = std::make_unique<ecs::MovementSystem>(&_world->entities, _renderer);
	std::unique_ptr<ecs::ParseInput> parseSys = std::make_unique<ecs::ParseInput>(&_world->entities,
		_renderer->getEventReceiver());

	_systemList.push_back(std::move(parseSys));
	_systemList.push_back(std::move(movPlayerSys));
	_systemList.push_back(std::move(movSys));
}


ids::IScene::sceneId ids::GameScene::run() {
	_initSystem();
	_renderer->setCameraFPS();
	_world->drawEntities();
	while (_renderer->isRunning() && !_event.isKeyDown(irr::KEY_ESCAPE)) {
		_renderer->render();
		if (!_event.hasEvent())
			continue;
		for (auto &it : _systemList) {
			it->update(1);
		}
	}
	return MENU;
}
