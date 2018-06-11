/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PowerUpRotationSystem
*/

#include "engine/systems/PowerUpRotationSystem.hpp"

ecs::PowerUpRotationSystem::PowerUpRotationSystem(const entityVector &allEntities,
	std::shared_ptr<gfx::Renderer> renderer)
	: System(allEntities), _renderer{renderer}
{
}

void ecs::PowerUpRotationSystem::update(double delta[[maybe_unused]])
{
	auto powerUps = getEntities(COMP_COLLECTIBLE, COMP_ORIENTATION, COMP_GRAPHIC);

	for (Entity *powerUp : powerUps) {
		auto &orientationComp = powerUp->getComponent<Orientation>();
		auto &gfxComp = powerUp->getComponent<Graphic>();
		orientationComp.orientation += 2;
		_renderer->rotate(gfxComp.sceneNode, {0, orientationComp.orientation, 0});
	}
}
