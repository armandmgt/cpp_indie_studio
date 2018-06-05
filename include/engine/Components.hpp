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
		bool invincibility;
		bool footPowerUp;
		std::size_t power;
		std::size_t maxBombs;
	};

	struct Explosion : public Component {
		static comp getType() { return COMP_EXPLOSION; };
		std::size_t power;
		std::size_t timeout;
	};

	struct Collectible : public Component {
		explicit Collectible(ActionTarget at) : action(at)
		{};
		static comp getType() { return COMP_COLLECTIBLE; };
		Collectible() = default;
		ActionTarget action;
	};

	struct Velocity : public Component {
		static comp getType() { return COMP_VELOCITY; };
		float x;
		float y;
	};

	struct Orientation : public Component{
		static comp getType() { return COMP_ORIENTATION; };
		float orientation;
	};

	struct Position : public Component {
		static comp getType() { return COMP_POSITION; };
		float x;
		float y;
	};

	struct Input : public Component {
		static comp getType() { return COMP_INPUT; };
		bool goLeft;
		bool goRight;
		bool goUp;
		bool goDown;
	};

	struct AiInput : public Component {
		static comp getType() { return COMP_AIINPUT; };
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
		irr::scene::ISceneNode *sceneNode;
	};
}
