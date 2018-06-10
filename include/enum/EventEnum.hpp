/*
** EPITECH PROJECT, 2018
** Enum
** File description:
** none
*/

#ifndef ENUM_HPP_
	#define ENUM_HPP_

	namespace evt {
		enum eventKey
		{
			UP, DOWN, RIGHT, LEFT, A, B, C, D, E, F, G, H,
			I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			SPACE, DELETE, ESCAPE, MOUSE
		};

		enum eventType {
			MOVEMENT, ACTION
		};

		enum eventAction
		{
			PUTBOMB, MOVEUP, MOVEDOWN, MOVERIGHT, MOVELEFT,
			PAUSE, RESTART, MENU, QUIT, CLICK
		};
	}

#endif