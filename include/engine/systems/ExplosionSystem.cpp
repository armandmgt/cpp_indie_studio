/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ExplosionSystem
*/

#include "ExplosionSystem.hpp"

ecs::ExplosionSystem::ExplosionSystem(std::vector<ecs::Entity> *allEntities, gfx::Renderer *render)
		: System(allEntities, render) {}

void ecs::ExplosionSystem::update(double delta[[maybe_unused]]) {
	auto &entities = getEntities(COMP_POSITION, COMP_EXPLOSION);

	for (auto e : entities) {
		auto &position = e->getComponent<Position>();
		std::size_t power = e->getComponent<Explosion>().power;
		std::size_t timeout = e->getComponent<Explosion>().timeout;
	}
}