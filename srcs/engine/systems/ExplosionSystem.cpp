/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ExplosionSystem
*/

#include "engine/systems/ExplosionSystem.hpp"

ecs::ExplosionSystem::ExplosionSystem(std::vector<ecs::Entity> *allEntities)
		: System(allEntities) {}

void ecs::ExplosionSystem::update(double delta[[maybe_unused]]) {
	auto &entities = getEntities(COMP_POSITION, COMP_EXPLOSION);

	for (auto e : entities) {
		auto &position = e->getComponent<Position>();
		std::size_t power = e->getComponent<Explosion>().power;
		std::size_t timeout = e->getComponent<Explosion>().timeout;
	}
}