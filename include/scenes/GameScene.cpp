/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** gamescene
*/

#include "GameScene.hpp"

ids::GameScene::GameScene(gfx::Renderer *r) {
	auto *w = new ecs::World(r);

	this->_world = std::make_unique<ecs::World>(*w);
	this->_renderer = std::make_unique<gfx::Renderer>(*r);
}

std::unique_ptr<ecs::World> &ids::GameScene::getWorld() {
	return _world;
}

ids::IScene::sceneId ids::GameScene::run() {

	return GAME;
}
