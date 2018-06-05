/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Settings
*/

#include "menu/Settings.hpp"

ids::menu::Settings::Settings(gfx::Renderer *rend) : AMenu(rend, SETTINGS)
{
	_infoButtons.emplace_back((struct button){vec2d<int>(480,1000), vec2d<int>(107,55), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/play-button.png",
						  "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-play-button.png", GAME, false});
	_infoButtons.emplace_back((struct button){vec2d<int>(750,1000), vec2d<int>(195,53), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/scores-button.png",
						  "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-scores-button.png", SCORE, false});
	_infoButtons.emplace_back((struct button){vec2d<int>(1100,1000), vec2d<int>(143,53), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/back-button.png",
						  "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-back-button.png", MENU, false});
	_infoButtons.emplace_back((struct button){vec2d<int>(1400,1000), vec2d<int>(101,63), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/quit-button.png",
						  "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-quit-button.png", QUIT, false});
	_backgroundImg = "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/backgound/background-default.png";
	_items.emplace_back((struct items){"Sound", ON, "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/volume.png",
		 "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/mute.png", vec2d<int>(928, 510)});
	_items.emplace_back((struct items){"Board", NONE, "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/Items/score-board.png",
					   "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/Items/score-board.png", vec2d<int>(480, 180)});
	setWindow();
	settingsItems();
}

ids::menu::Settings::~Settings()
{
	_rend->clearScene();
}

void ids::menu::Settings::settingsItems()
{
	for (auto &item : _items) {
		_rend->load2D(item.soundOn, item.pos);
	}
}

void ids::menu::Settings::setMusicLevel()
{

}