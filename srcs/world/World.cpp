/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** world
*/
#include <engine/Components.hpp>
#include <functional>
#include <memory>
#include "map/Map.hpp"
#include "world/World.hpp"

namespace ecs {

	void world::destroyEntity(entityId id) {
		_world.erase(id);

	}

	void world::_spawnEntitiesFromMap(std::vector<std::string> &&gameMap) {
		for (auto itR = gameMap.begin(); itR != gameMap.end(); itR++) {
			for (auto itC = itR->begin(); itC != itR->end(); itC++) {
				switch (*itC) {
					case BREAKABLE_WALL:
						_spawnWall(WALL, itC - itR->begin(), itR - gameMap.begin());
						break;
					case UNBREAKABLE_WALL:
						_spawnWall(U_WALL, itC - itR->begin(), itR - gameMap.begin());
						break;
					case MAP_PLAYER:
						_spawnPlayer(itC - itR->begin(), itR - gameMap.begin());

				}
			}
		}
	}

	entityId world::createEntity(entityType type)
	{
		static std::unordered_map<entityType, std::bitset<Entity::bitSize>> const concordMap = {
			{PLAYER,  COMP_POSITION | COMP_VELOCITY |
				  COMP_CHARACTER | COMP_DESTRUCTIBLE | COMP_GRAPHIC},
			{POWERUP, COMP_POSITION | COMP_COLLECTIBLE | COMP_GRAPHIC},
			{BOMB,    COMP_VELOCITY | COMP_EXPLOSION | COMP_GRAPHIC},
			{U_WALL, COMP_POSITION | COMP_COLLECTIBLE | COMP_GRAPHIC},
			{WALL, COMP_POSITION | COMP_COLLECTIBLE | COMP_GRAPHIC},
			{FLAMME,  COMP_POSITION},
		};

		std::bitset<Entity::bitSize> EntityBit(concordMap.at(type));
		Entity newEntity(EntityBit);
		_world.emplace(curId++, newEntity);
		return _world.size() - 1;
	}

	bool world::addComponent(entityId id, Position pos)
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_POSITION)) == COMP_POSITION) {
			_world.at(id).cPosition = pos;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Character chara)
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_CHARACTER)) == COMP_CHARACTER) {
			_world.at(id).cCharacter = chara;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Explosion exp)
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_EXPLOSION)) == COMP_EXPLOSION) {
			_world.at(id).cExplosion = exp;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Collectible col)
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_COLLECTIBLE)) == COMP_COLLECTIBLE) {
			_world.at(id).cCollectible = col;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Velocity vel)
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY) {
			_world.at(id).cVelocity = vel;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Input in)
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_INPUT)) == COMP_INPUT) {
			_world.at(id).cInput = in;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, AiInput in)
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_AIINPUT)) == COMP_AIINPUT) {
			_world.at(id).cAiInput = in;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Destructible des)
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_DESTRUCTIBLE)) == COMP_DESTRUCTIBLE) {
			_world.at(id).cDestructible = des;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Graphic gfx)
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_GRAPHIC)) == COMP_GRAPHIC) {
			_world.at(id).cGfx = gfx;
			return true;
		}
		return false;
	}

	void world::_spawnWall(entityType  type, size_t posX, size_t posY) {
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Destructible des {(!(type == WALL)), nullptr};

		entityId id = createEntity(type == WALL ? WALL : U_WALL);
		addComponent(id, pos);
		addComponent(id, des);
	}

	void world::_spawnPlayer(size_t posX, size_t posY)
	{
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Velocity vel {0.f, 0.f};
		Character chara {false, false, 1, 1};
		Destructible des {true, nullptr};

		entityId id = createEntity(PLAYER);
		addComponent(id, pos);
		addComponent(id, vel);
		addComponent(id, chara);
		addComponent(id, des);
	}

	void world::drawEntities()
	{
		for (auto &it : _world) {
			std::cout << "Type : [" << it.first << "]" << std::endl;
			if ((it.second.bit & std::bitset<Entity::bitSize>(COMP_POSITION)) == COMP_POSITION)
				std::cout << "Position : [" << it.second.cPosition.x << ", " << it.second.cPosition.y << "]" << std::endl;
			if ((it.second.bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY)
				std::cout << "Velocity : [" << it.second.cVelocity.x << ", " << it.second.cVelocity.y << "]" << std::endl;

		}
	}

}
