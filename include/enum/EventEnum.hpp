/*
** EPITECH PROJECT, 2018
** Enum
** File description:
** none
*/

#ifndef ENUM_HPP_
	#define ENUM_HPP_

	namespace ids {

		enum eventKey
		{
			NONE, UP, DOWN, RIGHT, LEFT, A, B, C, D, E, F, G, H,
			I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			SPACE, DELE, ESCAPE, MOUSE
		};

		enum eventAction
		{
			NOTHING, XPLOSE, PUTBOMB, PUTITEM, MOVEUP,
			MOVEDOWN, MOVERIGHT, MOVELEFT, PAUSE, RESTART, MENU,
			QUIT, CLICK
		};

		enum type_t
		{
			ACTION,
			KEY
		};
	}

#endif