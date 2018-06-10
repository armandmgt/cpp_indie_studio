/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MovementSystem
*/

#include <iostream>
#include "engine/systems/MovementSystem.hpp"

namespace ecs {
	MovementSystem::MovementSystem(entityVector allEntities, std::shared_ptr<gfx::Renderer> render)
		: System(allEntities), _renderer(render)
	{
	}

	bool MovementSystem::_isValidPosition(float x, float y)
	{
		auto entities = getEntities(COMP_POSITION);

		for (auto &entitie : entities) {
			if (!entitie->hasComponent<Character>() && !entitie->hasComponent<Explosion>() &&
			    !entitie->hasComponent<Collectible>()) {
				auto &posE = entitie->getComponent<Position>();
				auto posP = roundPos<int>(x, y);
				auto posRounded = roundPos<int>(posE.x, posE.y);
				if (posP.x == posRounded.x && posP.y == posRounded.y)
					return false;
			}
		}
		return true;
	}

	void MovementSystem::update(double delta[[maybe_unused]]) {
		auto entities = getEntities(COMP_POSITION, COMP_VELOCITY);

		for (auto e : entities) {
			auto &position = e->getComponent<Position>();
			auto &velocity = e->getComponent<Velocity>();
			if (velocity.x == 0.0f && velocity.y == 0.0f) {
				if (e->hasComponent<Graphic>())
					_setAnimation(e, false);
				continue;
			}
			if (_isValidPosition(position.x + velocity.x, position.y))
				position.x += velocity.x;
			if (_isValidPosition(position.x, position.y + velocity.y))
				position.y += velocity.y;
			if (e->hasComponent<Graphic>()) {
				auto &gfxComponent = e->getComponent<Graphic>();
				_renderer->setPosition(gfxComponent.sceneNode, {position.x, 0, position.y});
				_setAnimation(e, true);
			}
			velocity.x = 0;
			velocity.y = 0;
		}
	}

	void MovementSystem::_setAnimation(Entity *entity, bool walk) {
		auto &gfxComponent = entity->getComponent<Graphic>();
		auto *animatedSceneNode = static_cast<irr::scene::IAnimatedMeshSceneNode *>(gfxComponent.sceneNode);
		if (walk)
			_renderer->setAnimation(animatedSceneNode, "walk");
		else
			_renderer->stopAnimation(animatedSceneNode, "walk");
	}
};