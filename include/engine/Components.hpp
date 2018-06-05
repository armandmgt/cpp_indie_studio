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
		MAXBOMBS,
		FOOTPOWERUP,
		POWER,
	};

	enum comp : std::size_t {
		COMP_CHARACTER,
		COMP_EXPLOSION,
		COMP_COLLECTIBLE,
		COMP_VELOCITY,
		COMP_POSITION,
		COMP_INPUT,
		COMP_AIINPUT,
		COMP_DESTRUCTIBLE,
		COMP_GRAPHIC,
		COMP_ORIENTATION,
	};

	struct Component {

	};

	struct Character : public Component {
		static comp getType() { return COMP_CHARACTER; };
		Character(bool i, bool f, std::size_t p , std::size_t m) : invincibility(i),
									   footPowerUp(f),
									   power(p),
									   maxBombs(m)
		{};
		~Character() = default;
		bool invincibility;
		bool footPowerUp;
		std::size_t power;
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
		static comp getType() { return COMP_COLLECTIBLE; };
		Collectible() = default;
		~Collectible() = default;
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
		static comp getType() { return COMP_ORIENTATION; };
		explicit Orientation(float ori) : orientation(ori)
		{};
		~Orientation() = default;
		float orientation;
	};

	struct Position : public Component {
		static comp getType() { return COMP_POSITION; };
		Position(float d, float v) : x(d), y(v)
		{};
		~Position() = default;
		float x;
		float y;
	};

	struct Input : public Component {
		static comp getType() { return COMP_INPUT; };
		Input(bool l, bool r, bool u, bool d) : goLeft(l), goRight(r), goUp(u), goDown(d)
		{};
		~Input() = default;
		bool goLeft;
		bool goRight;
		bool goUp;
		bool goDown;
	};

	struct AiInput : public Component {
		static comp getType() { return COMP_AIINPUT; };
		AiInput(bool l, bool r, bool u, bool d) : goLeft(l), goRight(r), goUp(u), goDown(d)
		{};
		~AiInput() = default;
		bool goLeft;
		bool goRight;
		bool goUp;
		bool goDown;
	};

	struct Destructible : public Component {
		static comp getType() { return COMP_DESTRUCTIBLE; };
		bool  destructible;
		std::unique_ptr<Collectible> item;
	};

	struct Graphic : public Component {
		static comp getType() { return COMP_GRAPHIC; };
		explicit Graphic(irr::scene::ISceneNode *s) : sceneNode(s)
		{};
		~Graphic() = default;
		irr::scene::ISceneNode *sceneNode;
	};
}
