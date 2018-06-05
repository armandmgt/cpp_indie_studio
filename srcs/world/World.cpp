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

	Entity &world::createEntity(entityType type)
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
		_world.emplace_back(std::move(newEntity));
		return _world.back();
	}

	void world::destroyEntity(entityId id) {
		auto pos = _world.begin() + id;
		_world.erase(pos);
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
						_spawnWall(KICK,  itC - itR->begin(), itR - gameMap.begin());
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
		auto &ent = createEntity(WALL);
		addComponent(ent, pos);
		addComponent(ent, std::move(des));
		addComponent(ent, gfx);
	}

	void world::_spawnUWall(long posX, long posY) {
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Graphic gfx {renderer.createElem("../../assets/meshs/ground.obj")};

		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Could not load wall asset");
		auto &ent = createEntity(U_WALL);
		addComponent(ent, pos);
		addComponent(ent, gfx);
	}

	void world::_spawnBWall(long posX, long posY)
	{
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Destructible des {true, nullptr};
		Graphic gfx {renderer.createElem("../../assets/meshs/box.obj")};

		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Wall not load");
		renderer.addTexture(gfx.sceneNode, "../../assets/textures/box.jpg");
		auto &ent = createEntity(U_WALL);
  		addComponent(ent, pos);
		addComponent(ent, std::move(des));
		addComponent(ent, gfx);
	}

	void world::_spawnPlayer(long posX, long posY)
	{
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Velocity vel {0.f, 0.f};
		Character chara {false, false, 1, 1};
		Destructible des {true, nullptr};
		Orientation ori {0};
		Graphic gfx { renderer.createAnimatedElem("../../assets/meshs/ninja.b3d") };

		auto &ent = createEntity(PLAYER);
		addComponent(ent, pos);
		addComponent(ent, vel);
		addComponent(ent, chara);
		addComponent(ent, ori);
		addComponent(ent, gfx);
		addComponent(ent, std::move(des));
	}

	bool world::addComponent(Entity &ent, Position pos) noexcept
	{
		if ((ent.bit & std::bitset<Entity::bitSize>(COMP_POSITION)) == COMP_POSITION) {
			ent.cPosition = pos;
			return true;
		}
		return false;
	}

	bool world::addComponent(Entity &ent, Character chara) noexcept
	{
		if ((ent.bit & std::bitset<Entity::bitSize>(COMP_CHARACTER)) == COMP_CHARACTER) {
			ent.cCharacter = chara;
			return true;
		}
		return false;
	}

	bool world::addComponent(Entity &ent, Explosion exp) noexcept
	{
		if ((ent.bit & std::bitset<Entity::bitSize>(COMP_EXPLOSION)) == COMP_EXPLOSION) {
			ent.cExplosion = exp;
			return true;
		}
		return false;
	}

	bool world::addComponent(Entity &ent, Collectible col) noexcept
	{
		if ((ent.bit & std::bitset<Entity::bitSize>(COMP_COLLECTIBLE)) == COMP_COLLECTIBLE) {
			ent.cCollectible = col;
			return true;
		}
		return false;
	}

	bool world::addComponent(Entity &ent, Velocity vel) noexcept
	{
		if ((ent.bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY) {
			ent.cVelocity = vel;
			return true;
		}
		return false;
	}

	bool world::addComponent(Entity &ent, Input in) noexcept
	{
		if ((ent.bit & std::bitset<Entity::bitSize>(COMP_INPUT)) == COMP_INPUT) {
			ent.cInput = in;
			return true;
		}
		return false;
	}

	bool world::addComponent(Entity &ent, AiInput in) noexcept
	{
		if ((ent.bit & std::bitset<Entity::bitSize>(COMP_AIINPUT)) == COMP_AIINPUT) {
			ent.cAiInput = in;
			return true;
		}
		return false;
	}

	bool world::addComponent(Entity &ent, Destructible des) noexcept
	{
		if ((ent.bit & std::bitset<Entity::bitSize>(COMP_DESTRUCTIBLE)) == COMP_DESTRUCTIBLE) {
			ent.cDestructible = std::move(des);
			return true;
		}
		return false;
	}

	bool world::addComponent(Entity &ent, Graphic gfx) noexcept
	{
		if ((ent.bit & std::bitset<Entity::bitSize>(COMP_GRAPHIC)) == COMP_GRAPHIC) {
			ent.cGfx = gfx;
			return true;
		}
		return false;
	}

	bool world::addComponent(Entity &ent, Orientation orientation) noexcept
	{
		if ((ent.bit & std::bitset<Entity::bitSize>(COMP_ORIENTATION)) == COMP_ORIENTATION) {
			ent.cOrientation = orientation;
			return true;
		}
		return false;
	}

	void world::debug()
	{
		for (auto &it : _world) {
			std::cout << "Type : [" << it.id << "]" << std::endl;
			if ((it.bit & std::bitset<Entity::bitSize>(COMP_POSITION)) == COMP_POSITION)
				std::cout << "Position : [" << it.cPosition.x << ", " << it.cPosition.y << "]" << std::endl;
			if ((it.bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY)
				std::cout << "Velocity : [" << it.cVelocity.x << ", " << it.cVelocity.y << "]" << std::endl;
		}
	}

	Position &world::getPosition(entityId id) {
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_POSITION)) == COMP_POSITION) {
			return _world.at(id).cPosition;
		}
		throw std::logic_error("No position component");
	}

	Entity &world::getEntity(entityId id) {
		return this->_world.at(id);
	}

	Character &world::getCharacter(entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_CHARACTER)) == COMP_CHARACTER)
			return this->_world.at(id).cCharacter;
		throw std::logic_error("No character component");
	}

	Explosion &world::getExplosion(entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_EXPLOSION)) == COMP_EXPLOSION)
			return this->_world.at(id).cExplosion;
		throw std::logic_error("No Explosion component");
	}

	Collectible &world::getCollectible(entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_COLLECTIBLE)) == COMP_COLLECTIBLE)
			return this->_world.at(id).cCollectible;
		throw std::logic_error("No collectible component");
	}

	Velocity &world::getVelocity(entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY)
			return this->_world.at(id).cVelocity;
		throw std::logic_error("No velocity component");
	}

	Input &world::getInput(entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_INPUT)) == COMP_INPUT)
			return this->_world.at(id).cInput;
		throw std::logic_error("No input component");
	}

	Orientation &world::getOrientation(entityId id)
	{
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_ORIENTATION)) == COMP_ORIENTATION)
			return this->_world.at(id).cOrientation;
		throw std::logic_error("No orientation component");
	}

	AiInput &world::getAiInput(entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_AIINPUT)) == COMP_AIINPUT)
			return this->_world.at(id).cAiInput;
		throw std::logic_error("No AiInput component");
	}

	Destructible &world::getDestructible(entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_DESTRUCTIBLE)) == COMP_DESTRUCTIBLE)
			return this->_world.at(id).cDestructible;
		throw std::logic_error("No Destructible component");
	}

	Graphic &world::getGraphic(entityId id) {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_GRAPHIC)) == COMP_GRAPHIC)
			return this->_world.at(id).cGfx;
		throw std::logic_error("No Graphic component");
	}

	void world::systemSpawnBomb(entityId id) noexcept {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_CHARACTER)) == COMP_CHARACTER) {
			auto &ent = createEntity(BOMB);
			Velocity vel {0, 0};
			Explosion exp {this->_world.at(id).cCharacter.power, 5};
			Graphic gfx {renderer.createAnimatedElem("../../assets/meshs/bomb.obj")};

			if (gfx.sceneNode == nullptr)
				throw std::runtime_error("Wall not load");
			addComponent(ent, getPosition(id));
			addComponent(ent, vel);
			addComponent(ent, exp);
			addComponent(ent, gfx);
		}
	}

	void world::systemMove(entityId id) noexcept {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY) {
			auto &entity(this->_world.at(id));
			entity.cPosition.x += entity.cVelocity.x;
			entity.cPosition.y += entity.cVelocity.y;
		}
	}

	void world::systemSpawnCollectibleFromBox(entityId id) noexcept {
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_DESTRUCTIBLE)) == COMP_DESTRUCTIBLE) {
			auto &box(this->_world.at(id));
			auto &ent = createEntity(POWERUP);
			Graphic nGfx { renderer.createAnimatedElem(_queryMeshFromActionTarget(box.cCollectible.action).c_str())};

			addComponent(ent, box.cCollectible);
			addComponent(ent, box.cPosition);
			auto &pos = getPosition(id);
			renderer.setPosition(nGfx.sceneNode, {pos.x * sizeGround.x, 0 , pos.y * sizeGround.z});
			addComponent(ent, nGfx);
			_world.at(id).cGfx.sceneNode->remove();
			destroyEntity(id);
		}
	}

	//TODO: Check the collision between the item and the player
	void world::systemPickupItem(entityId iId, entityId pId) noexcept {
		// ...collision check ?
		auto &player(_world.at(pId));

		//TODO: event to end invincibility
		if ((_world.at(iId).bit & std::bitset<Entity::bitSize>(KICK)) == KICK)
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
		case KICK:
			return "../../assets/meshs/foot.obj";
		case MAXBOMBS:
			return "../../assets/meshs/max-bomb.obj";
		case FOOTPOWERUP:
			return "../../assets/meshs/speedup.obj";
		case POWER:
			return "../../assets/meshs/powerup.obj";
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
			if (((elem.bit & std::bitset<Entity::bitSize>(COMP_POSITION)) == COMP_POSITION) &&
				(elem.bit & std::bitset<Entity::bitSize>(COMP_GRAPHIC)) == COMP_GRAPHIC) {
				vec3d<float> pos {
					elem.cPosition.x * sizeGround.x,
					0,
					elem.cPosition.y * sizeGround.z
				};
				renderer.setPosition(elem.cGfx.sceneNode, pos);
			}
		}
	}
}
