/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#pragma once

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
		COMP_CHARACTER = 1 << 0,
		COMP_EXPLOSION = 1 << 1,
		COMP_COLLECTIBLE = 1 << 2,
		COMP_VELOCITY = 1 << 3,
		COMP_POSITION = 1 << 4,
		COMP_INPUT = 1 << 5,
		COMP_AIINPUT = 1 << 6,
		COMP_DESTRUCTIBLE = 1 << 7,
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
		ActionTarget action;
	};

	struct Velocity {
		float x;
		float y;
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
		Collectible *item;
	};
}
