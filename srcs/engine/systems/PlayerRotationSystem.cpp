/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PlayerRotationSystem
*/

#include <iostream>
#include "engine/systems/Systems.hpp"
#include "engine/systems/PlayerRotationSystem.hpp"

ecs::PlayerRotationSystem::PlayerRotationSystem(entityVector allEntities, std::shared_ptr <gfx::Renderer> renderer)
	: System(allEntities), _renderer{renderer}
{
}

void ecs::PlayerRotationSystem::update(double delta[[maybe_unused]])
{
	auto players = getEntities(COMP_CHARACTER, COMP_INPUT, COMP_GRAPHIC);

	for (auto player : players) {
			auto &input = player->getComponent<Input>();
			auto &gfx = player->getComponent<Graphic>();
			if (input.goRight) {
				_renderer->rotate(gfx.sceneNode, {0, 90, 0});
			} else if (input.goUp) {
				_renderer->rotate(gfx.sceneNode, {0, 0, 0});
			} else if (input.goDown) {
				_renderer->rotate(gfx.sceneNode, {0, 180, 0});
			} else if (input.goLeft) {
				_renderer->rotate(gfx.sceneNode, {0, -90, 0});
			}
	}
}
