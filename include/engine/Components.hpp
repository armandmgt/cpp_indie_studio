/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include <memory>
#include <chrono>

namespace ecs {
	enum actionTarget {
		KICK,
		MAX_BOMBS,
		SPEEDUP,
		POWER,
	};

	enum comp : std::size_t {
		COMP_CHARACTER,
		COMP_EXPLOSION,
		COMP_COLLECTIBLE,
		COMP_VELOCITY,
		COMP_POSITION,
		COMP_INPUT,
		COMP_AI_INPUT,
		COMP_DESTRUCTIBLE,
		COMP_GRAPHIC,
		COMP_ORIENTATION,
		COMP_EPHEMERE,
		COMP_DAMAGE,
		MAX_COMPONENTS
	};

	struct Component {

	};

	struct Character : public Component {
		Character(bool footPowerUp, int power, size_t speed, long maxBombs, std::size_t i)
			: footPowerUp(footPowerUp), power(power), speed(speed), maxBombs(maxBombs), id(i)
		{};
		~Character() = default;
		static comp const type = COMP_CHARACTER;
		bool footPowerUp;
		int power;
		std::size_t speed;
		long maxBombs;
		std::size_t id;
	};

	struct Explosion : public Component {
		Explosion(std::size_t ownerId, int p) : ownerId{ownerId},power(p)
		{};
		~Explosion() = default;
		static comp const type = COMP_EXPLOSION;
		std::size_t ownerId;
		int power;
	};

	struct Collectible : public Component {
		explicit Collectible(actionTarget at) :
			action(at)
		{};
		~Collectible() = default;
		static comp const type = COMP_COLLECTIBLE;
		actionTarget action;
	};

	struct Velocity : public Component {
		Velocity(float w, float v) : x(w), y(v)
		{};
		~Velocity() = default;
		static comp const type = COMP_VELOCITY;
		float x;
		float y;
	};

	struct Orientation : public Component{
		explicit Orientation(float ori) : orientation(ori)
		{};
		~Orientation() = default;
		static comp const type = COMP_ORIENTATION;
		float orientation;
	};

	struct Position : public Component {
		Position(float d, float v) : x(d), y(v)
		{};
		~Position() = default;
		static comp const type = COMP_POSITION;
		float x;
		float y;
	};

	struct Input : public Component {
		explicit Input(bool ai) : goLeft(false), goRight(false), goUp(false), goDown(false), putBomb(false), isAi(ai)
		{};
		~Input() = default;
		static comp const type = COMP_INPUT;
		bool goLeft;
		bool goRight;
		bool goUp;
		bool goDown;
		bool putBomb;
		bool isAi;
	};

	struct AiInput : public Component {
		AiInput(bool l, bool r, bool u, bool d, bool b) : goLeft(l), goRight(r), goUp(u), goDown(d), putBomb(b)
		{};
		~AiInput() = default;
		static comp const type = COMP_AI_INPUT;
		bool goLeft;
		bool goRight;
		bool goUp;
		bool goDown;
		bool putBomb;
	};

	struct Destructible : public Component {
		explicit Destructible(std::unique_ptr<Collectible> item)
			: item(std::move(item))
		{};
		~Destructible() = default;
		static comp const type = COMP_DESTRUCTIBLE;
		std::unique_ptr<Collectible> item;
	};

	struct Damage : public Component {
		explicit Damage(bool d)
		: isDamage(d)
		{};
		~Damage() = default;
		static comp const type = COMP_DAMAGE;
		bool isDamage;
	};

	struct Graphic : public Component {
		explicit Graphic(irr::scene::ISceneNode *s, float scalling = 1.f) :
				sceneNode(s), scale(scalling)
		{};
		~Graphic() = default;
		static comp const type = COMP_GRAPHIC;
		irr::scene::ISceneNode *sceneNode;
		float scale;
	};

	struct Ephemere : public Component {
		Ephemere(std::size_t t, std::chrono::time_point<std::chrono::steady_clock> ti) :
			timeout(t), time(ti)
		{
		};
		~Ephemere() = default;
		static comp const type = COMP_EPHEMERE;
		std::size_t timeout;
		std::chrono::time_point<std::chrono::steady_clock> time;
	};

}
