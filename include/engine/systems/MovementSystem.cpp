/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MovementSystem
*/

#include "MovementSystem.hpp"

namespace ecs {
	MovementSystem::MovementSystem(entityVector allEntities, gfx::Renderer *render)
		: System(allEntities), _renderer(render)
	{
	}

	void MovementSystem::update(double delta[[maybe_unused]]) {
		auto entities = getEntities(COMP_POSITION, COMP_VELOCITY);

		for (auto &e : entities) {
			auto &position = e->getComponent<Position>();
			auto &velocity = e->getComponent<Velocity>();
			position.x += velocity.x;
			position.y += velocity.y;
			velocity.x = 0;
			velocity.y = 0;
			if (e->hasComponent<Graphic>()) {
				auto &gfxEntitie = e->getComponent<Graphic>();
				_renderer->setPosition(gfxEntitie.sceneNode, {position.x, 0, position.y});
			}
		}
	}
};