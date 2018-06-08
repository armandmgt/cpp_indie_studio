/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Launch
*/

#include <iostream>
#include "menu/Launch.hpp"

ids::menu::Launch::Launch(gfx::Renderer *rend) : AMenu(rend, MENU), _events{rend->getEventReceiver()},
	_items{
		{"bomberman", 0, "../assets/menu/Items/bomber-man.png", {600, 400}},
		{"speak-bubble", 5, "../assets/menu/Items/speak-bubble.png", {1350, 450}},
		{"welcome-message", 5, "../assets/menu/Items/welcome-message.png", {1410, 530}}
	}
{
	_infoButtons = {
		{{1570, 670}, {107, 55}, "../assets/menu/buttons/default/play-button.png",
		        "../assets/menu/buttons/active/a-play-button.png", GAME, false},
		{{1520, 750}, {195, 53}, "../assets/menu/buttons/default/scores-button.png",
		        "../assets/menu/buttons/active/a-scores-button.png", SCORE, false},
		{{1500, 820}, {235, 64}, "../assets/menu/buttons/default/settings-button.png",
		        "../assets/menu/buttons/active/a-settings-button.png", SETTINGS, false},
		{{1570, 900}, {101, 63}, "../assets/menu/buttons/default/quit-button.png",
		        "../assets/menu/buttons/active/a-quit-button.png", QUIT, false}
	};
	_backgroundImg = "../assets/menu/background/menu-background.png";
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

ids::IScene::sceneId ids::menu::Launch::run()
{
	setWindow();
	decorateScene();
	while (_rend->isRunning() && _id == MENU) {
		if (_events.isKeyDown(irr::KEY_ESCAPE)) {
			_id = ids::IScene::QUIT;
			return _id;
		}
		auto mousePos = _events.getMousePosition();
		std::cout << mousePos.position.X << " " << mousePos.position.Y << std::endl;
		//if (_rend->isKeyPressed(irr::KEY_LBUTTON)) {

		computeEvent(mousePos);
		_rend->render();
	}
	_rend->clearScene();
	return _id;
}