/*
** EPITECH PROJECT, 2018
** Enum
** File description:
** none
*/

#pragma once

namespace evt {
	enum eventKey
	{
		NONE, UP, DOWN, RIGHT, LEFT, A, B, C, D, E, F, G, H,
		I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		SPACE, DELETE, ESCAPE, MOUSE, MAX_KEY
	};

		enum eventType {
			MOVEMENT, ACTION
		};enum eventAction
		{
			NOTHING, MOVEUP, MOVEDOWN,  MOVELEFT, MOVERIGHT, PUTBOMB,
			PAUSE, RESTART, MENU, QUIT, CLICK, MAX_ACTION
		};
	}

inline std::ostream &operator<<(std::ostream &os, evt::eventKey e) {
	static const std::array<std::string, evt::MAX_KEY> association = {
		"NONE", "UP", "DOWN", "RIGHT", "LEFT", "A", "B", "C", "D", "E", "F", "G", "H",
		"I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
		"SPACE", "DELETE", "ESCAPE", "MOUSE"
	};

	return os << association[e];
}

inline std::ostream &operator<<(std::ostream &os, evt::eventAction e) {
	static const std::array<std::string, evt::MAX_ACTION> association = {
		"NOTHING", "MOVEUP", "MOVEDOWN", "MOVELEFT", "MOVERIGHT", "PUTBOMB",
		"PAUSE", "RESTART", "MENU", "QUIT", "CLICK"
	};

	return os << association[e];
}

