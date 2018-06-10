/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Pause
*/

#include "menu/Pause.hpp"

ids::menu::Pause::Pause(std::shared_ptr<gfx::Renderer> rend, std::shared_ptr<ids::Music> music)
	: AMenu{rend, music, PAUSE}, _events{_rend->getEventReceiver()}
{
	_infoButtons = {
		{{950, 400}, {143, 53}, "../assets/menu/buttons/default/back-button.png",
			"../assets/menu/buttons/active/a-back-button.png", GAME, false},
		{{900, 500}, {235, 64}, "../assets/menu/buttons/default/settings-button.png",
			"../assets/menu/buttons/active/a-settings-button.png", SETTINGS, false},
		{{965, 600}, {101, 63}, "../assets/menu/buttons/default/quit-button.png",
			"../assets/menu/buttons/active/a-quit-button.png", QUIT, false}
	};
	_backgroundImg = "../assets/menu/background/menu-pause-bomberman.png";
}

ids::menu::Pause::~Pause()
{
}

ids::IScene::sceneId ids::menu::Pause::run()
{
	setWindow();
	while (_rend->isRunning() && _events.isKeyDown(irr::KEY_ESCAPE));
	while (_rend->isRunning() && _id == PAUSE) {
		if (_events.isKeyDown(irr::KEY_ESCAPE)) {
			_id = ids::IScene::GAME;
			return _id;
		}
		_mouseData= _events.getMousePosition();
		buttonEvent();
		_rend->render();
	}
	return _id;
}