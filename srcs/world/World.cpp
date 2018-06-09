/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** World
*/

#include "engine/systems/MovementSystem.hpp"
#include "engine/systems/ExplosionSystem.hpp"
#include "engine/Components.hpp"
#include "world/World.hpp"

namespace ecs {

	World::World(gfx::Renderer *render) : entities{}, renderer{render}
	{
		systems.push_back(std::make_unique<MovementSystem>(&entities));
	}

	Entity &World::createEntity()
	{
		entities.emplace_back();
		return entities.back();
	}

	void World::destroyEntity(entityId id) {
		entities.erase(entities.begin() + id);
	}

	void World::spawnEntitiesFromMap(std::vector<std::string> &&gameMap) {
		for (auto itR = gameMap.begin(); itR != gameMap.end(); itR++) {
			for (auto itC = itR->begin(); itC != itR->end(); itC++) {
				switch (*itC) {
					case BREAKABLE_WALL:
						spawnBWall(itC - itR->begin(), itR - gameMap.begin());
						break;
					case UNBREAKABLE_WALL:
						spawnUWall(itC - itR->begin(), itR - gameMap.begin());
						break;
					case MAP_PLAYER:
						spawnPlayer(itC - itR->begin(), itR - gameMap.begin());
						break;
					case FIRE_UP:
						spawnWall(POWER, itC - itR->begin(), itR - gameMap.begin());
						break;
					case BOMB_UP:
						spawnWall(MAX_BOMBS, itC - itR->begin(), itR - gameMap.begin());
						break;
					case SPEED_UP:
						spawnWall(SPEEDUP, itC - itR->begin(), itR - gameMap.begin());
						break;
					case POWER_UP:
						spawnWall(KICK, itC - itR->begin(), itR - gameMap.begin());
						break;
					default:
						break;
				}
			}
		}
	}

	void World::spawnWall(ActionTarget type, long posX, long posY) {
		auto &ent = createEntity();

		ent.addComponent<Destructible>(std::make_unique<Collectible>(type));
		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Graphic>(renderer->createElem("../assets/meshs/box.obj"));

		auto const &gfx= ent.getComponent<Graphic>();
		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Cannot load box asset");
		renderer->addTexture(gfx.sceneNode, "../assets/textures/box.jpg");
	}

	void World::spawnUWall(long posX, long posY) {
		static int rand = 0;
		auto &ent = createEntity();

		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Graphic>(renderer->createElem(
			rand % 2 ? "../assets/meshs/wallBlue.obj" : "../assets/meshs/wallGreen.obj"));
		rand++;

		auto const &gfx = ent.getComponent<Graphic>();
		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Could not load wall asset");
	}

	void World::spawnBWall(long posX, long posY)
	{
		auto &ent = createEntity();

		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Destructible>(nullptr);
		ent.addComponent<Graphic>(renderer->createElem("../assets/meshs/box.obj"));

		auto const &gfx = ent.getComponent<Graphic>();
		if (gfx.sceneNode == nullptr || !renderer->addTexture(gfx.sceneNode, "../assets/textures/box.jpg"))
			throw std::runtime_error("Cannot load wall asset");
	}

	void World::spawnPlayer(long posX, long posY)
	{
		static std::size_t playerId;
		auto &ent = createEntity();

		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Velocity>(0.f, 0.f);
		ent.addComponent<Character>(false, 1LU, 1LU, 1LU, playerId++);
		ent.addComponent<Destructible>(nullptr);
		ent.addComponent<Orientation>(0.f);
		ent.addComponent<Graphic>(renderer->createAnimatedElem("../assets/meshs/ninja.b3d"), 2);
	}

	void World::spawnFlames(ecs::Position initialPos, size_t pwr) {
		//std::cout << "[SPAWN] flammes at [" << initialPos.x << ":" << initialPos.y << "] with power (" << pwr << ")" << std::endl;

		auto &e = createEntity();
		for (size_t i = 0; i < pwr; i++) {
			e.addComponent<Position>(initialPos.x + i, initialPos.y);
			e.addComponent<Position>(initialPos.x, initialPos.y + i);
			e.addComponent<Position>(initialPos.x - i, initialPos.y);
			e.addComponent<Position>(initialPos.x, initialPos.y - i);
		}
		e.addComponent<Orientation>(0.f);
		e.addComponent<Graphic>(renderer->createAnimatedElem("../assets/meshs/ninja.b3d"));
	}

	void World::debug()
	{
		for (auto &it : entities) {
			if (it.hasComponent<Position>())
				std::cout << "Position : [" << it.getComponent<Position>().x << ", " << it.getComponent<Position>().y << "]"
										     << std::endl;
			if (it.hasComponent<Velocity>())
				std::cout << "Velocity : [" << it.getComponent<Velocity>().x << ", " << it
					.getComponent<Velocity>().y << "]" << std::endl;
		}
	}

	void World::spawnBombSystem(entityId id) {
		if (entities.at(id).hasComponent<Character>()) {
			auto &ent = createEntity();

			ent.addComponent<Velocity>(0.f, 0.f);
			ent.addComponent<Explosion>(entities.at(id).getComponent<Character>().power, 5LU);
			ent.addComponent<Graphic>(renderer->createAnimatedElem("../assets/meshs/bomb.obj"));

			auto const &gfx= ent.getComponent<Graphic>();
			if (gfx.sceneNode == nullptr)
				throw std::runtime_error("Cannot load bomb asset");
		}
	}


	void World::spawnCollectibleFromBoxSystem(entityId id) noexcept {
		if (entities.at(id).hasComponent<Destructible>()) {
			auto &box = this->entities.at(id);
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

	irr::core::stringw World::_queryMeshFromActionTarget(const ActionTarget act) const {
		switch (act) {
		case KICK:
			return "../assets/meshs/foot.obj";
		case MAX_BOMBS:
			return "../assets/meshs/max-bomb.obj";
		case SPEEDUP:
			return "../assets/meshs/speedup.obj";
		case POWER:
			return "../assets/meshs/powerup.obj";
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
		for (auto &elem : entities) {
			if (elem.hasComponent<Position>() && elem.hasComponent<Graphic>()) {
				vec3d<float> pos {
					elem.getComponent<Position>().x * sizeGround.x,
					0,
					elem.getComponent<Position>().y * sizeGround.z
				};
				renderer->setPosition(elem.getComponent<Graphic>().sceneNode, pos);
				if (elem.hasComponent<Character>() && elem.hasComponent<Graphic>()) {
					auto comp = elem.getComponent<Graphic>();
					renderer->setScale(comp.sceneNode, comp.scale);
				}
			}
		}
	}

	Entity &World::getEntity(entityId id) {
		return entities.at(id);
	}

	void World::update(long delta) {
		for (auto &s : systems) {
			s->update(delta);
		}
	}
}
