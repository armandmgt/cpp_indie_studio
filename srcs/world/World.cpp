/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** World
*/

#include <chrono>
#include "engine/systems/MovementSystem.hpp"
#include "engine/systems/ExplosionSystem.hpp"
#include "engine/Components.hpp"
#include "world/World.hpp"

namespace ecs {

	using entityVectorType = std::vector<std::unique_ptr<Entity>>;
	World::World(std::shared_ptr<gfx::Renderer> render) : entities{std::make_shared<entityVectorType>()}, _renderer{render}
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
						spawnEmptyBox(itC - itR->begin(), itR - gameMap.begin());
						break;
					case UNBREAKABLE_WALL:
						spawnWall(itC - itR->begin(), itR - gameMap.begin());
						break;
					case MAP_PLAYER:
						spawnPlayer(itC - itR->begin(), itR - gameMap.begin());
						break;
					case FIRE_UP:
						spawnFilledBox(POWER, itC - itR->begin(), itR - gameMap.begin());
						break;
					case BOMB_UP:
						spawnFilledBox(MAX_BOMBS, itC - itR->begin(), itR - gameMap.begin());
						break;
					case SPEED_UP:
						spawnFilledBox(SPEEDUP, itC - itR->begin(), itR - gameMap.begin());
						break;
					case POWER_UP:
						spawnFilledBox(KICK, itC - itR->begin(), itR - gameMap.begin());
						break;
					default:
						break;
				}
			}
		}
	}

	void World::spawnFilledBox(actionTarget type, long posX, long posY) {
		auto &ent = createEntity();

		ent.addComponent<Destructible>(std::make_unique<Collectible>(type));
		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Graphic>(_renderer->createElem("../assets/meshs/box.obj"));

		auto const &gfx= ent.getComponent<Graphic>();
		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Cannot load box asset");
		_renderer->addTexture(gfx.sceneNode, "../assets/textures/box.jpg");
	}

	void World::spawnEmptyBox(long posX, long posY)
	{
		auto &ent = createEntity();

		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Destructible>(nullptr);
		ent.addComponent<Graphic>(_renderer->createElem("../assets/meshs/box.obj"));

		auto const &gfx = ent.getComponent<Graphic>();
		if (gfx.sceneNode == nullptr || !_renderer->addTexture(gfx.sceneNode, "../assets/textures/box.jpg"))
			throw std::runtime_error("Cannot load wall asset");
	}

	void World::spawnWall(long posX, long posY) {
		static int rand = 0;
		auto &ent = createEntity();

		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Graphic>(_renderer->createElem(
			rand % 2 ? "../assets/meshs/wallBlue.obj" : "../assets/meshs/wallGreen.obj"));
		rand++;

		auto const &gfx = ent.getComponent<Graphic>();
		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Could not load wall asset");
	}

	void World::spawnPlayer(long posX, long posY)
	{
		static std::size_t playerId;
		auto &ent = createEntity();

		ent.addComponent<Position>(static_cast<float>(posX), static_cast<float>(posY));
		ent.addComponent<Velocity>(0.f, 0.f);
		ent.addComponent<Input>(playerId == 0 || playerId == 3);
		ent.addComponent<Character>(false, 1, 1LU, 1L, playerId++);
		ent.addComponent<Destructible>(nullptr);
		ent.addComponent<Orientation>(0.f);
		ent.addComponent<Graphic>(_renderer->createAnimatedElem("../assets/meshs/ninja.b3d"), 2.f);

		auto &gfx = ent.getComponent<Graphic>();
		auto *animatedSceneNode = static_cast<irr::scene::IAnimatedMeshSceneNode *>(gfx.sceneNode);
		_renderer->addAnimation(animatedSceneNode, "walk", {0, 10});
		_renderer->addAnimation(animatedSceneNode, "stop", {5, 5});
		_renderer->setAnimation(animatedSceneNode, "stop");
		_renderer->setAnimationSpeed(animatedSceneNode, 0.f);
	}

	void World::spawnBombSystem(Entity *player) {
		if (player->hasComponent<Character>()) {
			auto &ent = createEntity();
			auto &posPlayer = player->getComponent<Position>();
			vec2d<int> posBomb = roundPos<int>(posPlayer.x, posPlayer.y);

			ent.addComponent<Explosion>(player->id, player->getComponent<Character>().power);
			ent.addComponent<Ephemere>(4LU, std::chrono::steady_clock::now());
			ent.addComponent<Graphic>(_renderer->createAnimatedElem("../assets/meshs/bomb.obj"));
			ent.addComponent<Position>(static_cast<float>(posBomb.x), static_cast<float>(posBomb.y));

			auto const &gfx= ent.getComponent<Graphic>();
			if (gfx.sceneNode == nullptr)
				throw std::runtime_error("Cannot load bomb asset");
			auto &pos = ent.getComponent<Position>();
			_renderer->setPosition(gfx.sceneNode, {pos.x, 0, pos.y});
		}
	}

	void World::spawnCollectibleFromBox(Entity *box) noexcept {
		auto &ent = createEntity();
		auto &col = box->getComponent<Destructible>();
		auto &pos = box->getComponent<Position>();

		ent.addComponent<Collectible>(col.item->action);
		ent.addComponent<Orientation>(0.f);
		ent.addComponent<Position>(box->getComponent<Position>());
		ent.addComponent<Destructible>(nullptr);
		ent.addComponent<Graphic>(_renderer->createElem(
			_queryMeshFromActionTarget(col.item->action)
		));

		auto const &gfx = ent.getComponent<Graphic>();
		if (gfx.sceneNode == nullptr)
			throw std::runtime_error("Cannot load wall asset");
		_renderer->setPosition(gfx.sceneNode, {pos.x, 0, pos.y});
	}

	irr::core::stringw World::_queryMeshFromActionTarget(const actionTarget act) const {
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
				if (!(node = _renderer->createElem(assetPath))) {
					return;
				}
				_renderer->setPosition(node, pos);
				if (x == 0) {
					_sizeGround = _renderer->getSize(node);
					_renderer->setSizeGround(_sizeGround);
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
				_renderer->setPosition(elem->getComponent<Graphic>().sceneNode, pos);
				if (elem->hasComponent<Character>() && elem->hasComponent<Graphic>()) {
					auto comp = elem->getComponent<Graphic>();
					_renderer->setScale(comp.sceneNode, comp.scale);
				}
			}
		}
	}

	void World::destroyEntity(std::size_t &id) {
		auto it = std::find_if(entities->begin(), entities->end(), [id] (const std::unique_ptr<Entity> &e) {
			return e->id == id;
		});
		if ((*it)->hasComponent<Graphic>()) {
			auto &gfxComp = (*it)->getComponent<Graphic>();
			gfxComp.sceneNode->remove();
		}
		entities->erase(it);
	}

	entityVector World::getEntities()
	{
		return entities;
	}

	bool World::isValidPosition(float x, float y)
	{
		for (auto &entitie : *entities) {
			if (entitie->hasComponent<Position>() && !entitie->hasComponent<Destructible>()) {
				auto &posE = entitie->getComponent<Position>();
				if (posE.x == x && posE.y == y)
					return false;
			}
		}
		return true;
	}

	void World::spawnFlameAtPosition(float x, float y) {
		auto &e = createEntity();
		e.addComponent<Orientation>(0.f);
		e.addComponent<Position>(x, y);
		e.addComponent<Ephemere>(1LU, std::chrono::steady_clock::now());
		e.addComponent<Graphic>(_renderer->createAnimatedElem("../assets/meshs/flames.obj"));
		e.addComponent<Damage>(true);
		auto &posE = e.getComponent<Position>();
		_renderer->setPosition(e.getComponent<Graphic>().sceneNode, {posE.x, 0, posE.y});

	}

	void World::spawnFlames(ecs::Position initialPos, int pwr) {
		spawnFlameAtPosition(initialPos.x, initialPos.y);
		for (auto i = 1; i <= pwr  && isValidPosition(initialPos.x, initialPos.y + i); i++)
			spawnFlameAtPosition(initialPos.x, initialPos.y + i);
		for (auto i = 1; i <= pwr  && isValidPosition(initialPos.x + i, initialPos.y); i++)
			spawnFlameAtPosition(initialPos.x + i, initialPos.y);
		for (auto i = -1; i >= (pwr * -1)  && isValidPosition(initialPos.x, initialPos.y + i); i--)
			spawnFlameAtPosition(initialPos.x, initialPos.y + i);
		for (auto i = -1; i >= (pwr * -1) && isValidPosition(initialPos.x + i, initialPos.y); i--)
			spawnFlameAtPosition(initialPos.x + i, initialPos.y);
	}
}
