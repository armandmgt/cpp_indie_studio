/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** World
*/

#include <ctime>
#include <chrono>
#include "engine/systems/MovementSystem.hpp"
#include "engine/systems/ExplosionSystem.hpp"
#include "engine/Components.hpp"
#include "world/World.hpp"

namespace ecs {

	using entityVectorType = std::vector<std::unique_ptr<Entity>>;
	World::World(gfx::Renderer *render) : entities{std::make_shared<entityVectorType>()}, renderer{render}
	{
	}

	Entity &World::createEntity()
	{
		entities->push_back(std::make_unique<Entity>());
		return *entities->back();
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
		ent.addComponent<Character>(false, 1, 1LU, 1LU, playerId++);
		ent.addComponent<Destructible>(nullptr);
		ent.addComponent<Orientation>(0.f);
		ent.addComponent<Input>(false);
		ent.addComponent<Graphic>(renderer->createAnimatedElem("../assets/meshs/ninja.b3d"), 2.f);
	}

	void World::spawnFlames(ecs::Position initialPos, int pwr) {
		for (auto i = pwr * (-1); i <= pwr; i++) {
			auto &e = createEntity();
			e.addComponent<Orientation>(0.f);
			e.addComponent<Position>(initialPos.x, initialPos.y - i);
			e.addComponent<Ephemere>(3LU, std::chrono::steady_clock::now());
			e.addComponent<Graphic>(renderer->createAnimatedElem("../assets/meshs/ninja.b3d"));
			e.addComponent<Damage>(true);
			auto &posE = e.getComponent<Position>();
			renderer->setPosition(e.getComponent<Graphic>().sceneNode, {posE.x, 0, posE.y});
		}
		for (auto i = pwr * (-1); i <= pwr; i++) {
			auto &e = createEntity();
			e.addComponent<Orientation>(0.f);
			e.addComponent<Position>(initialPos.x - i, initialPos.y);
			e.addComponent<Ephemere>(3LU, std::chrono::steady_clock::now());
			e.addComponent<Graphic>(renderer->createAnimatedElem("../assets/meshs/ninja.b3d"));
			e.addComponent<Damage>(true);
			auto &posE = e.getComponent<Position>();
			renderer->setPosition(e.getComponent<Graphic>().sceneNode, {posE.x, 0, posE.y});
		}
	}

	void World::spawnBombSystem(Entity *player) {
		if (player->hasComponent<Character>()) {
			auto &ent = createEntity();
			auto &posPlayer = player->getComponent<Position>();
			vec2d<int> posBomb = toIntegerPos<int>(posPlayer.x, posPlayer.y);

			ent.addComponent<Explosion>(player->getComponent<Character>().power);
			ent.addComponent<Ephemere>(5LU, std::chrono::steady_clock::now());
			ent.addComponent<Graphic>(renderer->createAnimatedElem("../assets/meshs/bomb.obj"));
			ent.addComponent<Position>(static_cast<float>(posBomb.x), static_cast<float>(posBomb.y));

			auto const &gfx= ent.getComponent<Graphic>();
			if (gfx.sceneNode == nullptr)
				throw std::runtime_error("Cannot load bomb asset");
			auto &pos = ent.getComponent<Position>();
			renderer->setPosition(gfx.sceneNode, {pos.x, 0, pos.y});
		}
	}

	void World::spawnCollectibleFromBoxSystem(Entity *box) noexcept {
		if (box->hasComponent<Destructible>() && box->getComponent<Destructible>().item != nullptr) {
			auto &ent = createEntity();

			std::cerr << "Get Collectible on box : " << box->id << std::endl;
			ent.addComponent<Collectible>(box->getComponent<Collectible>());
			std::cerr << "Get Position on box : " << box->id << std::endl;
			ent.addComponent<Position>(box->getComponent<Position>());
			std::cerr << "Get Destructible on box : " << box->id << std::endl;
			ent.addComponent<Graphic>(renderer->createElem(
				_queryMeshFromActionTarget(box->getComponent<Destructible>().item->action)
			));

			box->getComponent<Graphic>().sceneNode->remove();
			destroyEntity(box->id);
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
				if (x == 0) {
					sizeGround = renderer->getSize(node);
					renderer->setSizeGround(sizeGround);
				}
				pos.z += 1;
			}
			pos.z = 0;
			pos.x += 1;
		}
	}

	void World::drawEntities() {
		for (auto &elem : *entities) {
			if (elem->hasComponent<Position>() && elem->hasComponent<Graphic>()) {
				vec3d<float> pos {
					elem->getComponent<Position>().x,
					0,
					elem->getComponent<Position>().y
				};
				renderer->setPosition(elem->getComponent<Graphic>().sceneNode, pos);
				if (elem->hasComponent<Character>() && elem->hasComponent<Graphic>()) {
					auto comp = elem->getComponent<Graphic>();
					renderer->setScale(comp.sceneNode, comp.scale);
				}
			}
		}
	}

	void World::destroyEntity(std::size_t &id) {
		std::remove_if(entities->begin(), entities->end(), [id] (const std::unique_ptr<Entity> &e) {
			return e->id == id;
		});
	}

	entityVector World::getEntities()
	{
		return entities;
	}
}
