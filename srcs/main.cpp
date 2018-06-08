/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <string>
#include <iostream>
#include "engine/GameContainer.hpp"
#include "../include/common/Music.hpp"

int main()
{
	//ids::Music music;
//	std::string song = "/home/sandra/delivery/TEK2/cpp_indie_studio/assets/MusicFiles/oyeah.wav";
//	auto id = music.createMusic(song);
//	music.playMusic(id);

	try {
		ids::GameContainer gc;
		gc.start();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 84;
	}
	return 0;
}