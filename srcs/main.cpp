/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <string>
#include <iostream>
#include <memory>
#include <chrono>
#include "engine/GameContainer.hpp"

int main()
{
	try {
		ids::GameContainer gc;
		gc.start();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 84;
	}
	return 0;
}
