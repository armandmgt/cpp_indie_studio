/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <string>
#include <iostream>
#include "engine/GameContainer.hpp"

int main(int argc, char const *argv[])
{
	static const std::map<std::string, std::array<irr::EKEY_CODE, 5>> keymaps{
		{"fr",{irr::KEY_KEY_O, irr::KEY_KEY_L, irr::KEY_KEY_K, irr::KEY_KEY_M, irr::KEY_KEY_I}},
		{"us",{irr::KEY_KEY_I, irr::KEY_KEY_K, irr::KEY_KEY_J, irr::KEY_KEY_L, irr::KEY_KEY_U}}
	};

	auto keymap = keymaps.at("fr");
	if (argc > 1) {
		if (argv[1] == std::string("--keymap") && argc >= 3)
			keymap = keymaps.at(argv[2]);
		else
			std::cerr << "unknown option: " << argv[1] << std::endl;
	}
//	try {
		ids::GameContainer gc{keymap};
		gc.start();
//	} catch (const std::exception &e) {
//		std::cerr << e.what() << std::endl;
//		return 84;
//	}
	return 0;
}