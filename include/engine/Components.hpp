/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include <cstddef>
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
		Character(bool footPowerUp, size_t power, size_t speed, size_t maxBombs)
			: footPowerUp(footPowerUp), power(power), speed(speed), maxBombs(maxBombs)
		{};
		~Character() = default;
		static comp getType() { return COMP_CHARACTER; };
		bool footPowerUp;
		std::size_t power;
		std::size_t speed;
		std::size_t maxBombs;
	};

	struct Explosion : public Component {
		static comp getType() { return COMP_EXPLOSION; };
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
		static comp getType() { return COMP_COLLECTIBLE; };
		ActionTarget action;
	};

	struct Velocity : public Component {
		Velocity(float w, float v) : x(w), y(v)
		{};
		~Velocity() = default;
		static comp getType() { return COMP_VELOCITY; };
		float x;
		float y;
	};

	struct Orientation : public Component{
		explicit Orientation(float ori) : orientation(ori)
		{};
		~Orientation() = default;
		static comp getType() { return COMP_ORIENTATION; };
		float orientation;
	};

	struct Position : public Component {
		Position(float d, float v) : x(d), y(v)
		{};
		~Position() = default;
		static comp getType() { return COMP_POSITION; };
		float x;
		float y;
	};

	struct Input : public Component {
		Input(bool l, bool r, bool u, bool d) : goLeft(l), goRight(r), goUp(u), goDown(d)
		{};
		~Input() = default;
		static comp getType() { return COMP_INPUT; };
		bool goLeft;
		bool goRight;
		bool goUp;
		bool goDown;
		bool putBomb;
	};

	struct AiInput : public Component {
		AiInput(bool l, bool r, bool u, bool d) : goLeft(l), goRight(r), goUp(u), goDown(d)
		{};
		~AiInput() = default;
		static comp getType() { return COMP_AI_INPUT; };
		bool goLeft;
		bool goRight;
		bool goUp;
		bool goDown;
		bool putBomb;
	};

	struct Destructible : public Component {
		Destructible(bool destructible, std::unique_ptr<Collectible> item)
			: destructible(destructible), item(std::move(item))
		{};
		~Destructible() = default;
		static comp getType() { return COMP_DESTRUCTIBLE; };
		bool  destructible;
		std::unique_ptr<Collectible> item;
	};

	struct Graphic : public Component {
		explicit Graphic(irr::scene::ISceneNode *s) : sceneNode(s)
		{};
		~Graphic() = default;
		static comp getType() { return COMP_GRAPHIC; };
		irr::scene::ISceneNode *sceneNode;
	};
}
