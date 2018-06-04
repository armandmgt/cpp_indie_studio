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
		INVINCIBILITY,
		MAXBOMBS,
		FOOTPOWERUP,
		POWER,
	};

	enum comp : std::size_t {
		COMP_NONE = 0,
		COMP_CHARACTER = 1U << 0,
		COMP_EXPLOSION = 1U << 1,
		COMP_COLLECTIBLE = 1U << 2,
		COMP_VELOCITY = 1U << 3,
		COMP_POSITION = 1U << 4,
		COMP_INPUT = 1U << 5,
		COMP_AIINPUT = 1U << 6,
		COMP_DESTRUCTIBLE = 1U << 7,
		COMP_GRAPHIC = 1U << 8,
		COMP_ORIENTATION = 1U << 9,
	};

	struct Character {
		bool invincibility;
		bool footPowerUp;
		std::size_t power;
		std::size_t maxBombs;
	};

	struct Explosion {
		std::size_t power;
		std::size_t timeout;
	};

	struct Collectible {
		explicit Collectible(ActionTarget at) : action(at)
		{};
		Collectible() = default;
		ActionTarget action;
	};

	struct Velocity {
		float x;
		float y;
	};

	struct Orientation {
		float orientation;
	};

	struct Position {
		float x;
		float y;
	};

	struct Input {
		bool goLeft;
		bool goRight;
		bool goUp;
		bool goDown;
	};

	struct AiInput {
		bool goLeft;
		bool goRight;
		bool goUp;
		bool goDown;
	};

	struct Destructible {
		bool  destructible;
		std::unique_ptr<Collectible> item;
	};

	struct Graphic {
		irr::scene::ISceneNode *sceneNode;
	};
}
