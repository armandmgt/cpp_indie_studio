/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Launch
*/

#include <iostream>
#include "menu/Launch.hpp"

ids::menu::Launch::Launch(gfx::Renderer *rend) : AMenu(rend, MENU)
{
	std::cout << "Launch\n";
	_infoButtons.emplace_back((struct button){vec2d<int>(1570,670), vec2d<int>(107,55), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/play-button.png",
						  "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-play-button.png", GAME, false});
	_infoButtons.emplace_back((struct button){vec2d<int>(1520,750), vec2d<int>(195,53), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/scores-button.png",
						  "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-scores-button.png", SCORE, false});
	_infoButtons.emplace_back((struct button){vec2d<int>(1500,820), vec2d<int>(235,64), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/settings-button.png",
						  "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-settings-button.png", SETTINGS, false});
	_infoButtons.emplace_back((struct button){vec2d<int>(1570,900), vec2d<int>(101,63), "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/default/quit-button.png",
						  "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/buttons/active/a-quit-button.png", QUIT, false});
	_items.emplace_back((struct items){"bomberman", 0, "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/Items/bomber-man.png", vec2d<int>(600, 400)});
	_items.emplace_back((struct items){"speak-bubble", 5, "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/Items/speak-bubble.png", vec2d<int>(1350, 450)});
	_items.emplace_back((struct items){"welcome-message", 5, "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/Items/welcome-message.png", vec2d<int>(1410, 530)});
	_backgroundImg = "/home/sandra/delivery/TEK2/cpp_indie_studio/srcs/Menu/assets/backgound/menu-background.png";
	runPage();
}

ids::menu::Launch::~Launch()
{
	_rend->clearScene();
}

void ids::menu::Launch::decorateScene()
{

	for (auto &item : _items) {
		_rend->load2D(item.path, item.pos);
	}
}

ids::IScene::SceneId ids::menu::Launch::runPage()
{
	setWindow();
	decorateScene();
	while (_rend->isRun() && _id != SETTINGS && _id != QUIT) {
		if (_rend->isKeyPressed(irr::KEY_ESCAPE)) {
			_id = ids::IScene::QUIT;
			std::cout << "QUIT\n";
			return _id;
		}
		auto mousePos = _rend->getMousePosition();
		std::cout << mousePos.x << " " << mousePos.y << std::endl;
		//if (_rend->isKeyPressed(irr::KEY_LBUTTON)) {

		computeEvent({mousePos, true});
		_rend->render();
	}
	return _id;
}