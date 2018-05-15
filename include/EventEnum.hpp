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
			NONE, UP, DOWN, RIGHT, LEFT, PAUSE, RESTART, MENU,
			QUIT, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
			Q, R, S, T, U, V, W, X, Y, Z
		};

		enum eventAction
		{
			NOTHING, XPLOSE, PUTBOMB, PUTITEM, MOVEUP,
			MOVEDOWN, MOOVERIGHT, MOVELEFT
		};
	}

#endif