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

void ecs::PlayerRotationSystem::update(double delta)
{
	auto players = getEntities(COMP_CHARACTER, COMP_VELOCITY, COMP_GRAPHIC);

	for (auto player : players) {
			auto &velocity = player->getComponent<Velocity>();
			auto &gfx = player->getComponent<Graphic>();
			if (velocity.x == 0 && velocity.y == 0)
				continue;
			if (std::max(velocity.x, velocity.y) > 0) {
				if (std::max(velocity.x, velocity.y) == velocity.x) {
					std::cout << 1 << std::endl;
					_renderer->rotate(gfx.sceneNode, {0, 90, 0});
				} else {
					std::cout << 2 << std::endl;
					_renderer->rotate(gfx.sceneNode, {0, 0, 0});
				}
			} else {
				if (std::max(velocity.x, velocity.y) == velocity.x) {
					_renderer->rotate(gfx.sceneNode, {0, 180, 0});
				} else {
					std::cout << 4 << std::endl;
					_renderer->rotate(gfx.sceneNode, {0, -90, 0});
				}
			}
	}
}
