/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PowerUpPickupSystem
*/

#include <iostream>
#include "engine/systems/PowerUpPickupSystem.hpp"

ecs::PowerUpPickupSystem::PowerUpPickupSystem(const entityVector &allEntities, std::shared_ptr<ecs::World> world)
	: System(allEntities), _world{world}
{
}

void ecs::PowerUpPickupSystem::update(double delta)
{
	auto players = getEntities(COMP_CHARACTER, COMP_POSITION);

	for (Entity *player : players) {
		auto &playerPos = player->getComponent<Position>();
		auto &stats = player->getComponent<Character>();
		auto powerUps = getEntities(COMP_COLLECTIBLE, COMP_POSITION);
		for (Entity *powerUp : powerUps) {
			if (_pickedUp(playerPos, powerUp)) {
				actionTarget action = powerUp->getComponent<Collectible>().action;
				switch (action) {
				case MAX_BOMBS:
					stats.maxBombs += 1;
					break;
				case SPEEDUP:
					stats.speed += 1;
					break;
				case POWER:
					stats.power += 1;
					break;
				case KICK:
					stats.footPowerUp = true;
					break;
				}
				_world->destroyEntity(powerUp->id);
			}
		}
	}
}

bool ecs::PowerUpPickupSystem::_pickedUp(Position &playerPos, ecs::Entity *powerUp)
{
	auto &powerUpPos = powerUp->getComponent<Position>();
	auto rPowerUpPos = roundPos<float>(powerUpPos.x, powerUpPos.y);
	auto rPlayerPos = roundPos<float>(playerPos.x, playerPos.y);
	return rPlayerPos.x == rPowerUpPos.x && rPlayerPos.y == rPowerUpPos.y;
}
