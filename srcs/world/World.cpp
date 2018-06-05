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
		static std::unordered_map<entityType, std::vector<int>> const concordMap = {
			{PLAYER,  {COMP_POSITION , COMP_VELOCITY , COMP_CHARACTER , COMP_ORIENTATION ,
				COMP_DESTRUCTIBLE , COMP_GRAPHIC }},
			{POWERUP, {COMP_POSITION , COMP_COLLECTIBLE , COMP_GRAPHIC}},
			{BOMB, {COMP_POSITION , COMP_VELOCITY , COMP_EXPLOSION , COMP_GRAPHIC}},
			{U_WALL, {COMP_POSITION , COMP_GRAPHIC}},
			{WALL, {COMP_POSITION , COMP_DESTRUCTIBLE , COMP_GRAPHIC}},
			{FLAMME,  {COMP_POSITION}},
		};

		std::vector<int> EntityBit(concordMap.at(type));
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
		ent.addComponent(pos, std::move(des), gfx);
	}

	void world::_spawnUWall(long posX, long posY) {
		Position pos { static_cast<float>(posX), static_cast<float>(posY) };
		Graphic gfx {renderer.createElem("../../assets/meshs/ground.obj")};

		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Could not load wall asset");
		auto &ent = createEntity(U_WALL);
		ent.addComponent(pos, gfx);
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
  		ent.addComponent(pos, std::move(des), gfx);
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
		ent.addComponent(pos, vel, chara, ori, gfx, std::move(des));
	}

	void world::debug()
	{
		for (auto &it : _world) {
			std::cout << "Type : [" << it.id << "]" << std::endl;
			if ((it.bit & std::bitset<Entity::bitSize>(COMP_POSITION)) == COMP_POSITION)
				std::cout << "Position : [" << it.getComponent<Position>().x << ", " << it.getComponent<Position>().y << "]"
										     << std::endl;
			if ((it.bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY)
				std::cout << "Velocity : [" << it.getComponent<Velocity>().x << ", " << it
					.getComponent<Velocity>().y << "]" << std::endl;
		}
	}

	void world::systemSpawnBomb(entityId id) noexcept {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_CHARACTER)) == COMP_CHARACTER) {
			auto &ent = createEntity(BOMB);
			Velocity vel {0, 0};
			Explosion exp {_world.at(id).getComponent<Character>().power, 5};
			Graphic gfx {renderer.createAnimatedElem("../../assets/meshs/bomb.obj")};

			if (gfx.sceneNode == nullptr)
				throw std::runtime_error("Wall not load");
			ent.addComponent(_world.at(id).getComponent<Position>(), vel, exp, gfx);
		}
	}

	void world::systemMove(entityId id) noexcept {
		if ((this->_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_VELOCITY)) == COMP_VELOCITY) {
			auto &entity(this->_world.at(id));
			entity.getComponent<Position>().x += entity.getComponent<Velocity>().x;
			entity.getComponent<Position>().y += entity.getComponent<Velocity>().y;
		}
	}

	void world::systemSpawnCollectibleFromBox(entityId id) noexcept {
		if ((_world.at(id).bit & std::bitset<Entity::bitSize>(COMP_DESTRUCTIBLE)) == COMP_DESTRUCTIBLE) {
			auto &box= this->_world.at(id);
			auto &ent = createEntity(POWERUP);
			Graphic nGfx { renderer.createAnimatedElem(_queryMeshFromActionTarget(box.cCollectible.action).c_str())};

			auto &pos = box.getComponent<Position>();
			renderer.setPosition(nGfx.sceneNode, {pos.x * sizeGround.x, 0 , pos.y * sizeGround.z});
			ent.addComponent(box.getComponent<Collectible>(), box.getComponent<Position>(), nGfx);
			_world.at(id).getComponent<Graphic>().sceneNode->remove();
			destroyEntity(id);
		}
	}

	//TODO: Check the collision between the item and the player
	void world::systemPickupItem(entityId iId, entityId pId) noexcept {
		// ...collision check ?
		auto &player(_world.at(pId));

		//TODO: event to end invincibility
//		if ((_world.at(iId).bit & std::bitset<Entity::bitSize>(KICK)) == KICK)
//			player.cCharacter.invincibility = true;
//		if ((_world.at(iId).bit & std::bitset<Entity::bitSize>(MAXBOMBS)) == MAXBOMBS)
//			player.cCharacter.maxBombs++;
//		if ((_world.at(iId).bit & std::bitset<Entity::bitSize>(FOOTPOWERUP)) == FOOTPOWERUP)
//			player.cCharacter.footPowerUp = true;
//		if ((_world.at(iId).bit & std::bitset<Entity::bitSize>(POWER)) == POWER)
//			player.cCharacter.power++;
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
					elem.getComponent<Position>().x * sizeGround.x,
					0,
					elem.getComponent<Position>().y * sizeGround.z
				};
				renderer.setPosition(elem.getComponent<Graphic>().sceneNode, pos);
			}
		}
	}

	Entity &world::getEntity(entityId id)
	{
		return _world.at(id);
	}
}
