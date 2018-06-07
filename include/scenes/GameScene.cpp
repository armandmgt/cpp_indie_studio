/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** gamescene
*/

#include "GameScene.hpp"

ids::GameScene::GameScene(gfx::Renderer *r) {
	this->_world = std::make_unique<ecs::World>(new ecs::World(r));
}

ids::IScene::sceneId ids::GameScene::run() {
	return GAME;
}

std::unique_ptr<ecs::World> &ids::GameScene::getWorld() {
	return _world;
}
