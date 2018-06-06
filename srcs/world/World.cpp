/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** World
*/

#include <memory>
#include "engine/systems/MovementSystem.hpp"
#include "engine/Components.hpp"
#include "world/World.hpp"

namespace ecs {

	World::World(gfx::Renderer *render) : _entities{}, renderer{render}
	{
		_systems.push_back(std::make_unique<MovementSystem>(&_entities));
	}

	Entity &World::createEntity()
	{
		_entities.emplace_back();
		return _entities.back();
	}

	void World::destroyEntity(entityId id) {
		_entities.erase(_entities.begin() + id);
	}

	void World::_spawnEntitiesFromMap(std::vector<std::string> &&gameMap) {
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
						_spawnWall(MAX_BOMBS, itC - itR->begin(), itR - gameMap.begin());
						break;
					case SPEED_UP:
						_spawnWall(SPEEDUP, itC - itR->begin(), itR - gameMap.begin());
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

	void World::_spawnWall(ActionTarget type, long posX, long posY) {
		auto &ent = createEntity();
		std::cout << "spawning Wall" << std::endl;

		ent.addComponent<Destructible>(std::make_unique<Collectible>(type));
		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Graphic>(renderer->createElem("../../assets/meshs/box.obj"));

		auto const &gfx= ent.getComponent<Graphic>();
		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Cannot load box asset");
		renderer->addTexture(gfx.sceneNode, "../../assets/textures/box.jpg");
	}

	void World::_spawnUWall(long posX, long posY) {
		auto &ent = createEntity();
		std::cout << "spawning UWall" << std::endl;

		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Graphic>(renderer->createElem("../../assets/meshs/ground.obj"));

		auto const &gfx = ent.getComponent<Graphic>();
		std::cout << "got component" << std::endl;
		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Could not load wall asset");
	}

	void World::_spawnBWall(long posX, long posY)
	{
		std::cout << "spawning BWall" << std::endl;
		auto &ent = createEntity();

		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Destructible>(nullptr);
		ent.addComponent<Graphic>(renderer->createElem("../../assets/meshs/box.obj"));

		auto const &gfx = ent.getComponent<Graphic>();
		if (gfx.sceneNode == nullptr || !renderer->addTexture(gfx.sceneNode, "../../assets/textures/box.jpg"))
			throw std::runtime_error("Cannot load wall asset");
	}

	void World::_spawnPlayer(long posX, long posY)
	{
		std::cout << "spawning Player" << std::endl;
		auto &ent = createEntity();

		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Velocity>(0.f, 0.f);
		ent.addComponent<Character>(false, 1LU, 1LU, 1LU);
		ent.addComponent<Destructible>(nullptr);
		ent.addComponent<Orientation>(0.f);
		ent.addComponent<Graphic>(renderer->createAnimatedElem("../../assets/meshs/ninja.b3d"));
	}

	void World::debug()
	{
		for (auto &it : _entities) {
			if (it.hasComponent<Position>())
				std::cout << "Position : [" << it.getComponent<Position>().x << ", " << it.getComponent<Position>().y << "]"
										     << std::endl;
			if (it.hasComponent<Velocity>())
				std::cout << "Velocity : [" << it.getComponent<Velocity>().x << ", " << it
					.getComponent<Velocity>().y << "]" << std::endl;
		}
	}

	void World::systemSpawnBomb(entityId id) {
		if (_entities.at(id).hasComponent<Character>()) {
			auto &ent = createEntity();

			ent.addComponent<Velocity>(0.f, 0.f);
			ent.addComponent<Explosion>(_entities.at(id).getComponent<Character>().power, 5LU);
			ent.addComponent<Graphic>(renderer->createAnimatedElem("../../assets/meshs/bomb.obj"));

			auto const &gfx= ent.getComponent<Graphic>();
			if (gfx.sceneNode == nullptr)
				throw std::runtime_error("Cannot load bomb asset");
		}
	}

	void World::systemMove(entityId id) noexcept {
		if (_entities.at(id).hasComponent<Velocity>()) {
			auto &entity = this->_entities.at(id);

			auto &position = entity.getComponent<Position>();
			auto &velocity = entity.getComponent<Velocity>();
			position.x += velocity.x;
			position.y += velocity.y;
		}
	}

	void World::systemSpawnCollectibleFromBox(entityId id) noexcept {
		if (_entities.at(id).hasComponent<Destructible>()) {
			auto &box = this->_entities.at(id);
			auto &ent = createEntity();

			ent.addComponent<Collectible>(box.getComponent<Collectible>());
			ent.addComponent<Position>(box.getComponent<Position>());
			ent.addComponent<Graphic>(renderer->createElem(
				_queryMeshFromActionTarget(box.getComponent<Collectible>().action)
			));

			box.getComponent<Graphic>().sceneNode->remove();
			destroyEntity(id);
		}
	}

	//TODO: Check the collision between the item and the player
	void World::systemPickupItem(entityId iId[[maybe_unused]], entityId pId) noexcept {
		// ...collision check ?
		auto &player = _entities.at(pId);

		//TODO: event to end invincibility
//		if ((_entities.at(iId).bit & std::bitset<Entity::bitSize>(KICK)) == KICK)
//			player.cCharacter.invincibility = true;
//		if ((_entities.at(iId).bit & std::bitset<Entity::bitSize>(MAX_BOMBS)) == MAX_BOMBS)
//			player.cCharacter.maxBombs++;
//		if ((_entities.at(iId).bit & std::bitset<Entity::bitSize>(SPEEDUP)) == SPEEDUP)
//			player.cCharacter.footPowerUp = true;
//		if ((_entities.at(iId).bit & std::bitset<Entity::bitSize>(POWER)) == POWER)
//			player.cCharacter.power++;
	}

	void World::systemParseInput(const entityId id) noexcept {
		auto &player = _entities.at(id);
	}

	// ../../assets/meshs/ninja.b3d
	//TODO remove breaks
	irr::core::stringw World::_queryMeshFromActionTarget(const ActionTarget act) const {
		switch (act) {
		case KICK:
			return "../../assets/meshs/foot.obj";
		case MAX_BOMBS:
			return "../../assets/meshs/max-bomb.obj";
		case SPEEDUP:
			return "../../assets/meshs/speedup.obj";
		case POWER:
			return "../../assets/meshs/powerup.obj";
		default:
			throw std::logic_error("Unknown Action Target");
		}
	}

	void World::createGround(size_t xSize, size_t zSize, irr::core::stringw const &assetPath)
	{
		vec3d<float> pos{0, -7, 0};

		for (size_t x = 0; x < xSize; x++) {
			for (size_t z = 0; z < zSize; z++) {
				irr::scene::ISceneNode *node;
				if (!(node = renderer->createElem(assetPath))) {
					return;
				}
				renderer->setPosition(node, pos);
				if (x == 0)
					sizeGround = renderer->getSize(node);
				pos.z += sizeGround.z;
			}
			pos.z = 0;
			pos.x += sizeGround.x;
		}
	}

	void World::drawEntities() {
		for (auto &elem : _entities) {
			if (elem.hasComponent<Position>() && elem.hasComponent<Graphic>()) {
				vec3d<float> pos {
					elem.getComponent<Position>().x * sizeGround.x,
					0,
					elem.getComponent<Position>().y * sizeGround.z
				};
				renderer->setPosition(elem.getComponent<Graphic>().sceneNode, pos);
			}
		}
	}

	Entity &World::getEntity(entityId id) {
		return _entities.at(id);
	}

	void World::update(long delta) {
		for (auto &s : _systems) {
			s->update(delta);
		}
	}
}
