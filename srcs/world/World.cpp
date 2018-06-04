/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** world
*/

#include <functional>
#include <memory>
#include "engine/Components.hpp"
#include "world/World.hpp"

namespace ecs {

	world::world(gfx::Renderer &render) : curId(0), renderer(render)
	{

	}

	entityId world::createEntity(entityType type)
	{
		static std::unordered_map<entityType, std::bitset<Entity::bitSize>> const concordMap = {
			{PLAYER,  COMP_POSITION | COMP_VELOCITY |
				  COMP_CHARACTER | COMP_ORIENTATION | COMP_DESTRUCTIBLE | COMP_GRAPHIC},
			{POWERUP, COMP_POSITION | COMP_COLLECTIBLE | COMP_GRAPHIC},
			{BOMB,    COMP_POSITION | COMP_VELOCITY | COMP_EXPLOSION | COMP_GRAPHIC},
			{U_WALL, COMP_POSITION | COMP_COLLECTIBLE | COMP_GRAPHIC},
			{WALL, COMP_POSITION | COMP_COLLECTIBLE | COMP_GRAPHIC},
			{FLAMME,  COMP_POSITION},
		};

		std::bitset<Entity::bitSize> EntityBit(concordMap.at(type));
		Entity newEntity(EntityBit);
		_world.emplace(curId++, std::move(newEntity));
		return _world.size() - 1;
	}

	void world::destroyEntity(entityId id) {
		_world.erase(id);
	}

	void world::_spawnEntitiesFromMap(std::vector<std::string> &&gameMap) {
		for (auto itR = gameMap.begin(); itR != gameMap.end(); itR++) {
			for (auto itC = itR->begin(); itC != itR->end(); itC++) {
				switch (*itC) {
					case BREAKABLE_WALL:
						_spawnBWall(itC - itR->begin(), itR - gameMap.begin());
						break;
					case UNBREAKABLE_WALL:
						_spawnUWall( itC - itR->begin(), itR - gameMap.begin());
						break;
					case MAP_PLAYER:
						_spawnPlayer(itC - itR->begin(), itR - gameMap.begin());
						break;
					case FIRE_UP:
						_spawnWall(FIRE_UP, itC - itR->begin(), itR - gameMap.begin());
						break;
					case BOMB_UP:
						_spawnWall(BOMB_UP, itC - itR->begin(), itR - gameMap.begin());
						break;
					case SPEED_UP:
						_spawnWall(SPEED_UP, itC - itR->begin(), itR - gameMap.begin());
						break;
					case POWER_UP:
						_spawnWall(POWER_UP,  itC - itR->begin(), itR - gameMap.begin());
						break;
				}
			}
		}
	}

	void world::_spawnWall(mapItem type, long posX, long posY) {
		static std::unordered_map<mapItem, ActionTarget> const concordMap {{FIRE_UP, POWER},
										   {BOMB_UP, MAXBOMBS},
										   {SPEED_UP, FOOTPOWERUP},
										   {POWER_UP, INVINCIBILITY}
		};

		Destructible des {true , std::make_unique<Collectible>(concordMap.at(type))};
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		entityId id(createEntity(WALL));
		addComponent(id, pos);
		addComponent(id, std::move(des));
	}

	void world::_spawnUWall(long posX, long posY) {
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Graphic gfx {renderer.createAnimatedElem("../../assets/meshs/ground.obj")};

		entityId id(createEntity(U_WALL));
		addComponent(id, pos);
		addComponent(id, gfx);
	}

	void world::_spawnBWall(long posX, long posY)
	{
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Destructible des {true, nullptr};

		entityId id(createEntity(U_WALL));
		addComponent(id, pos);
		addComponent(id, std::move(des));
	}

	void world::_spawnPlayer(long posX, long posY)
	{
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Velocity vel {0.f, 0.f};
		Character chara {false, false, 1, 1};
		Destructible des {true, nullptr};
		Orientation ori {0};
		Graphic gfx {renderer.createAnimatedElem("../../assets/meshs/ninja.b3d")};

		entityId id(createEntity(PLAYER));
		addComponent(id, pos);
		addComponent(id, vel);
		addComponent(id, chara);
		addComponent(id, ori);
		addComponent(id, gfx);
		addComponent(id, std::move(des));
	}

	bool world::addComponent(entityId id, Position pos) noexcept
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_POSITION)) == COMP_POSITION) {
			_world.at(id).cPosition = pos;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Character chara) noexcept
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_CHARACTER)) == COMP_CHARACTER) {
			_world.at(id).cCharacter = chara;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Explosion exp) noexcept
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_EXPLOSION)) == COMP_EXPLOSION) {
			_world.at(id).cExplosion = exp;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Collectible col) noexcept
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_COLLECTIBLE)) == COMP_COLLECTIBLE) {
			_world.at(id).cCollectible = col;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Velocity vel) noexcept
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY) {
			_world.at(id).cVelocity = vel;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Input in) noexcept
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_INPUT)) == COMP_INPUT) {
			_world.at(id).cInput = in;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, AiInput in) noexcept
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_AIINPUT)) == COMP_AIINPUT) {
			_world.at(id).cAiInput = in;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Destructible des) noexcept
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_DESTRUCTIBLE)) == COMP_DESTRUCTIBLE) {
			_world.at(id).cDestructible = std::move(des);
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Graphic gfx) noexcept
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_GRAPHIC)) == COMP_GRAPHIC) {
			_world.at(id).cGfx = gfx;
			return true;
		}
		return false;
	}

	bool world::addComponent(entityId id, Orientation orientation) noexcept
	{
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_ORIENTATION)) == COMP_ORIENTATION) {
			_world.at(id).cOrientation = orientation;
			return true;
		}
		return false;
	}

	void world::debug()
	{
		for (auto &it : _world) {
			std::cout << "Type : [" << it.first << "]" << std::endl;
			if ((it.second.bit & std::bitset<Entity::bitSize>(COMP_POSITION)) == COMP_POSITION)
				std::cout << "Position : [" << it.second.cPosition.x << ", " << it.second.cPosition.y << "]" << std::endl;
			if ((it.second.bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY)
				std::cout << "Velocity : [" << it.second.cVelocity.x << ", " << it.second.cVelocity.y << "]" << std::endl;
		}
	}

	Position &world::getPosition(const entityId id) {
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_POSITION)) == COMP_POSITION) {
			return _world.at(id).cPosition;
		}
		throw std::logic_error("No position component");
	}

	Entity &world::getEntity(const entityId id) {
		return this->_world.at(id);
	}

	Character &world::getCharacter(const entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_CHARACTER)) == COMP_CHARACTER)
			return this->_world.at(id).cCharacter;
		throw std::logic_error("No character component");
	}

	Explosion &world::getExplosion(const entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_EXPLOSION)) == COMP_EXPLOSION)
			return this->_world.at(id).cExplosion;
		throw std::logic_error("No Explosion component");
	}

	Collectible &world::getCollectible(const entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_COLLECTIBLE)) == COMP_COLLECTIBLE)
			return this->_world.at(id).cCollectible;
		throw std::logic_error("No collectible component");
	}

	Velocity &world::getVelocity(const entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY)
			return this->_world.at(id).cVelocity;
		throw std::logic_error("No velocity component");
	}

	Input &world::getInput(const entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_INPUT)) == COMP_INPUT)
			return this->_world.at(id).cInput;
		throw std::logic_error("No input component");
	}

	Orientation &world::getOrientation(const entityId id)
	{
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_ORIENTATION)) == COMP_ORIENTATION)
			return this->_world.at(id).cOrientation;
		throw std::logic_error("No orientation component");
	}

	AiInput &world::getAiInput(const entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_AIINPUT)) == COMP_AIINPUT)
			return this->_world.at(id).cAiInput;
		throw std::logic_error("No AiInput component");
	}

	Destructible &world::getDestructible(const entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_DESTRUCTIBLE)) == COMP_DESTRUCTIBLE)
			return this->_world.at(id).cDestructible;
		throw std::logic_error("No Destructible component");
	}

	Graphic &world::getGraphic(const entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_GRAPHIC)) == COMP_GRAPHIC)
			return this->_world.at(id).cGfx;
		throw std::logic_error("No Graphic component");
	}

	void world::systemSpawnBomb(const entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_CHARACTER)) == COMP_CHARACTER) {
			entityId idBomb(createEntity(BOMB));
			Velocity vel {0, 0};
			Explosion exp {1, 5};

			addComponent(idBomb, getPosition(id));
			addComponent(idBomb, vel);
			addComponent(idBomb, exp);
		}
	}

	void world::systemMove(const entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY) {
			auto &entity(this->_world.at(id));
			entity.cPosition.x += entity.cVelocity.x;
			entity.cPosition.y += entity.cVelocity.y;
		}
	}

	void world::systemSpawnCollectibleFromBox(const entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_DESTRUCTIBLE)) == COMP_DESTRUCTIBLE) {
			auto &box(this->_world.at(id));
			const entityId newId(this->createEntity(POWERUP));
			const Graphic nGfx { renderer.createAnimatedElem(queryMeshFromActionTarget(box.cCollectible.action).c_str())};
			addComponent(newId, box.cCollectible);
			addComponent(newId, box.cPosition);
			addComponent(newId, nGfx);
			destroyEntity(id);
		}
	}

	// ../../assets/meshs/ninja.b3d
	std::string world::queryMeshFromActionTarget(const ActionTarget act) const {
		switch (act) {
		case INVINCIBILITY:
			return "../../assets/meshs/ninja.b3d";
			break;
		case MAXBOMBS:
			return "../../assets/meshs/ninja.b3d";
			break;
		case FOOTPOWERUP:
			return "../../assets/meshs/ninja.b3d";
			break;
		case POWER:
			return "../../assets/meshs/ninja.b3d";
			break;
		default:
			throw std::logic_error("Unkmown mesh");
		}
	}

	void world::createGround(size_t xSize, size_t zSize, irr::core::stringw const &assetPath)
	{
		vec3d<float> pos{0, -10, 0};

		for (size_t x = 0; x < xSize; x++) {
			vec3d<float> size(0,0,0);
			for (size_t z = 0; z < zSize; z++) {
				irr::scene::ISceneNode *node;
				if (!(node = renderer.createElem(assetPath))) {
					return;
				}
				renderer.setPosition(node, pos);
				size = renderer.getSize(node);
				pos.z += size.z;
			}
			pos.z = 0;
			pos.x += size.x;
		}
	}

	void world::drawEntities()
	{

	}
}
