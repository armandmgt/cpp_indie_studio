/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** gamescene
*/

#include <engine/systems/ExplosionSystem.hpp>
#include <engine/systems/DespawnSystem.hpp>
#include <engine/systems/BreakDestructibleSystem.hpp>
#include "engine/systems/PlayerMovement.hpp"
#include "engine/systems/MovementSystem.hpp"
#include "engine/systems/ParseInputSystem.hpp"
#include "engine/systems/PutBombSystem.hpp"
#include "GameScene.hpp"

ids::GameScene::GameScene(gfx::Renderer *r)
		: _world{std::make_shared<ecs::World>(r)}, _renderer{r}, _event{r->getEventReceiver()} {
	Map map(21, 20);

	map.initMap(20);
	map.printMap();
	_world->createGround(21, 20, "../assets/meshs/ground.obj");
	_world->spawnEntitiesFromMap(std::move(map.getMap()));
}

void ids::GameScene::_initSystem()
{
	_systemList.push_back(std::make_unique<ecs::ParseInput>(_world->getEntities(), _renderer->getEventReceiver()));
	_systemList.push_back(std::make_unique<ecs::PlayerMovement>(_world->getEntities()));
	_systemList.push_back(std::make_unique<ecs::MovementSystem>(_world->getEntities(), _renderer));
	_systemList.push_back(std::make_unique<ecs::PutBombSystem>(_world->getEntities(), _world));
	_systemList.push_back(std::make_unique<ecs::ExplosionSystem>(_world->getEntities(), _renderer, _world));
	_systemList.push_back(std::make_unique<ecs::DespawnSystem>(_world->getEntities(), _renderer, _world));
	_systemList.push_back(std::make_unique<ecs::BreakDestructibleSystem>(_world->getEntities(), _renderer, _world));
}


ids::IScene::sceneId ids::GameScene::run() {
	_initSystem();
	_renderer->setCameraFPS();
	_world->drawEntities();
	while (_renderer->isRunning() && !_event.isKeyDown(irr::KEY_ESCAPE)) {
		_renderer->render();
		_event.hasEvent();
		for (auto &it : _systemList) {
			it->update(1);
		}
	}
	return MENU;
}
