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
			{PLAYER,  COMP_POSITION | COMP_VELOCITY | COMP_CHARACTER | COMP_ORIENTATION |
				COMP_DESTRUCTIBLE | COMP_GRAPHIC},
			{POWERUP, COMP_POSITION | COMP_COLLECTIBLE | COMP_GRAPHIC},
			{BOMB, COMP_POSITION | COMP_VELOCITY | COMP_EXPLOSION | COMP_GRAPHIC},
			{U_WALL, COMP_POSITION | COMP_GRAPHIC},
			{WALL, COMP_POSITION | COMP_DESTRUCTIBLE | COMP_GRAPHIC},
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
						_spawnWall(POWER, itC - itR->begin(), itR - gameMap.begin());
						break;
					case BOMB_UP:
						_spawnWall(MAXBOMBS, itC - itR->begin(), itR - gameMap.begin());
						break;
					case SPEED_UP:
						_spawnWall(FOOTPOWERUP, itC - itR->begin(), itR - gameMap.begin());
						break;
					case POWER_UP:
						_spawnWall(INVINCIBILITY,  itC - itR->begin(), itR - gameMap.begin());
						break;
					default:
						break;
				}
			}
		}
	}

	void world::_spawnWall(ActionTarget type, long posX, long posY) {
		Destructible des {true , std::make_unique<Collectible>(type)};
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Graphic gfx {renderer.createElem("../../assets/meshs/box.obj")};

		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Wall not load");
		renderer.addTexture(gfx.sceneNode, "../../assets/textures/box.jpg");
		entityId id(createEntity(WALL));
		addComponent(id, pos);
		addComponent(id, std::move(des));
		addComponent(id, gfx);
	}

	void world::_spawnUWall(long posX, long posY) {
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Graphic gfx {renderer.createElem("../../assets/meshs/ground.obj")};

		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Could not load wall asset");
		entityId id(createEntity(U_WALL));
		addComponent(id, pos);
		addComponent(id, gfx);
	}

	void world::_spawnBWall(long posX, long posY)
	{
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Destructible des {true, nullptr};
		Graphic gfx {renderer.createElem("../../assets/meshs/box.obj")};

		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Wall not load");
		renderer.addTexture(gfx.sceneNode, "../../assets/textures/box.jpg");
		entityId id(createEntity(U_WALL));
  		addComponent(id, pos);
		addComponent(id, std::move(des));
		addComponent(id, gfx);
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

	void world::systemSpawnBomb(const entityId id) noexcept {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_CHARACTER)) == COMP_CHARACTER) {
			entityId idBomb(createEntity(BOMB));
			Velocity vel {0, 0};
			Explosion exp {1, 5}; //TODO use character's power

			addComponent(idBomb, getPosition(id));
			addComponent(idBomb, vel);
			addComponent(idBomb, exp);
		}
	}

	void world::systemMove(const entityId id) noexcept {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY) {
			auto &entity(this->_world.at(id));
			entity.cPosition.x += entity.cVelocity.x;
			entity.cPosition.y += entity.cVelocity.y;
		}
	}

	void world::systemSpawnCollectibleFromBox(const entityId id) noexcept {
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_DESTRUCTIBLE)) == COMP_DESTRUCTIBLE) {
			auto &box(this->_world.at(id));
			entityId newId(this->createEntity(POWERUP));
			Graphic nGfx { renderer.createAnimatedElem(_queryMeshFromActionTarget(box.cCollectible.action).c_str())};
			addComponent(newId, box.cCollectible);
			addComponent(newId, box.cPosition);
			_world.at(id).cGfx.sceneNode->remove();
			renderer.setPosition(nGfx.sceneNode, {_world.at(id).cPosition.x * sizeGround.x, 0 , _world.at
					(id).cPosition.y * sizeGround.z});
			addComponent(newId, nGfx);
			destroyEntity(id);
		}
	}

	//TODO: Check the collision between the item and the player
	void world::systemPickupItem(const entityId iId, const entityId pId) noexcept {
		// ...collision check ?
		auto &player(_world.at(pId));

		//TODO: event to end invincibility
		if ((_world.at(iId).bit & std::bitset<Entity::bitSize>(INVINCIBILITY)) == INVINCIBILITY)
			player.cCharacter.invincibility = true;
		if ((_world.at(iId).bit & std::bitset<Entity::bitSize>(MAXBOMBS)) == MAXBOMBS)
			player.cCharacter.maxBombs++;
		if ((_world.at(iId).bit & std::bitset<Entity::bitSize>(FOOTPOWERUP)) == FOOTPOWERUP)
			player.cCharacter.footPowerUp = true;
		if ((_world.at(iId).bit & std::bitset<Entity::bitSize>(POWER)) == POWER)
			player.cCharacter.power++;
	}

	// ../../assets/meshs/ninja.b3d
	//TODO remove breaks
	std::string world::_queryMeshFromActionTarget(const ActionTarget act) const {
		switch (act) {
		case INVINCIBILITY:
			return "../../assets/meshs/speedup.obj";
		case MAXBOMBS:
			return "../../assets/meshs/speedup.obj";
		case FOOTPOWERUP:
			return "../../assets/meshs/speedup.obj";
		case POWER:
			return "../../assets/meshs/speedup.obj";
		default:
			throw std::logic_error("Unknown Action Target");
		}
	}

	void world::createGround(size_t xSize, size_t zSize, irr::core::stringw const &assetPath)
	{
		vec3d<float> pos{0, -7, 0};

		for (size_t x = 0; x < xSize; x++) {
			for (size_t z = 0; z < zSize; z++) {
				irr::scene::ISceneNode *node;
				if (!(node = renderer.createElem(assetPath))) {
					return;
				}
				renderer.setPosition(node, pos);
				if (x == 0)
					sizeGround = renderer.getSize(node);
				pos.z += sizeGround.z;
			}
			pos.z = 0;
			pos.x += sizeGround.x;
		}
	}

	void world::drawEntities() {
		for (auto &elem : _world)
		{
			auto &entity = elem.second;
			if (((entity.bit & std::bitset<Entity::bitSize>(COMP_POSITION)) == COMP_POSITION) &&
				(entity.bit & std::bitset<Entity::bitSize>(COMP_GRAPHIC)) == COMP_GRAPHIC) {
				vec3d<float> pos {
					entity.cPosition.x * sizeGround.x,
					0,
					entity.cPosition.y * sizeGround.z
				};
				renderer.setPosition(entity.cGfx.sceneNode, pos);
			}
		}
		for (auto &elem : _world) {
			if ((elem.second.bit & std::bitset<Entity::bitSize>(COMP_DESTRUCTIBLE)) == COMP_DESTRUCTIBLE
			    && elem.second.cDestructible.item != nullptr) {
				std::cout << "Pos : " << elem.first << std::endl;
				systemSpawnCollectibleFromBox(elem.first);
			}
		}

	}
}
