/*
** EPITECH PROJECT, 2018
** indie
** File description:
** indie
*/

#pragma once

#include <cstddef>

namespace ecs {
	enum ActionTarget {
		INVINCIBILITY,
		MAXBOMBS,
		FOOTPOWERUP,
		POWER,
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
}