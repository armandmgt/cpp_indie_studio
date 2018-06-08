/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include <memory>

namespace ecs {
	enum ActionTarget {
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
		MAX_COMPONENTS
	};

	struct Component {

	};

	struct Character : public Component {
		Character(bool footPowerUp, size_t power, size_t speed, size_t maxBombs, std::size_t i)
			: footPowerUp(footPowerUp), power(power), speed(speed), maxBombs(maxBombs), id(i)
		{};
		~Character() = default;
		static comp const type = COMP_CHARACTER;
		bool footPowerUp;
		std::size_t power;
		std::size_t speed;
		std::size_t maxBombs;
		std::size_t id;
	};

	struct Explosion : public Component {
		static comp const type = COMP_EXPLOSION;
		Explosion(std::size_t p, std::size_t t) : power(p), timeout(t)
		{};
		~Explosion() = default;
		std::size_t power;
		std::size_t timeout;
	};

	struct Collectible : public Component {
		explicit Collectible(ActionTarget at) : action(at)
		{};
		~Collectible() = default;
		static comp const type = COMP_COLLECTIBLE;
		ActionTarget action;
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
		Input(bool l, bool r, bool u, bool d, bool b)
			: goLeft(l), goRight(r), goUp(u), goDown(d), putBomb(b)
		{};
		~Input() = default;
		static comp const type = COMP_INPUT;
		bool goLeft;
		bool goRight;
		bool goUp;
		bool goDown;
		bool putBomb;
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

	struct Graphic : public Component {
		explicit Graphic(irr::scene::ISceneNode *s) : sceneNode(s)
		{};
		~Graphic() = default;
		static comp const type = COMP_GRAPHIC;
		irr::scene::ISceneNode *sceneNode;
	};
}
