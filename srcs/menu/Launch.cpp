/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Launch
*/

#include <iostream>
#include "menu/Launch.hpp"

ids::menu::Launch::Launch(gfx::Renderer *rend, ids::Music *music) : AMenu(rend, MENU, music), _events{rend->getEventReceiver()},
	_items{
		{"bomberman", 0, "../assets/menu/Items/bomber-man.png", {600, 400}},
		{"speak-bubble", 5, "../assets/menu/Items/speak-bubble.png", {1350, 450}},
		{"welcome-message", 5, "../assets/menu/Items/welcome-message.png", {1410, 530}}
	}
{
	_infoButtons = {
		{{1570, 670}, {107, 55}, "../assets/menu/buttons/default/play-button.png",
		        "../assets/menu/buttons/active/a-play-button.png", GAME, false},
		{{1490, 740}, {270, 66}, "../assets/menu/buttons/default/loadgame-button.png",
		        "../assets/menu/buttons/active/a-loadgame-button.png", LOAD, false},
		{{1500, 820}, {235, 64}, "../assets/menu/buttons/default/settings-button.png",
		        "../assets/menu/buttons/active/a-settings-button.png", SETTINGS, false},
		{{1570, 900}, {101, 63}, "../assets/menu/buttons/default/quit-button.png",
		        "../assets/menu/buttons/active/a-quit-button.png", QUIT, false}
	};
	_backgroundImg = "../assets/menu/background/menu-background.png";
	if (_musicManager->musicInit()) {
		std::string audio = "../assets/MusicFiles/oyeah.wav";
		auto sample = _musicManager->createMusic(audio);
		_musicManager->playMusic(sample);
	}
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
		_mouseData = _events.getMousePosition();
		buttonEvent();
		_rend->render();
	}
	if (!_rend->isRunning())
		_id = ids::IScene::QUIT;
	_rend->clearScene();
	return _id;
}