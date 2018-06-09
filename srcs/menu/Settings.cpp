/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Settings
*/

#include "menu/Settings.hpp"

ids::menu::Settings::Settings(gfx::Renderer *rend, ids::Music *music) : AMenu(rend, SETTINGS, music), _events{rend->getEventReceiver()},
	_music{ON},
	_items{
		{{64, 64}, ON, "../assets/menu/volume.png", "../assets/menu/mute.png", {950, 510}},
		{{960, 720}, NONE, "../assets/menu/Items/score-board.png", "../assets/menu/Items/score-board.png",
			{480, 180}}
	}
{
	_infoButtons = {
		{{700,1000}, {107,55}, "../assets/menu/buttons/default/play-button.png",
			"../assets/menu/buttons/active/a-play-button.png", GAME, false},
		{{930, 1000}, {143,53}, "../assets/menu/buttons/default/back-button.png",
			"../assets/menu/buttons/active/a-back-button.png", MENU, false},
		{{1200,1000}, {101,63}, "../assets/menu/buttons/default/quit-button.png",
			"../assets/menu/buttons/active/a-quit-button.png", QUIT, false}
	};
	_backgroundImg = "../assets/menu/background/background-default.png";
}

ids::menu::Settings::~Settings()
{
	_rend->clearScene();
}

void	ids::menu::Settings::itemEvent()
{
	std::size_t id = 0;
	if (_mouse.state && inside_rect(_items[0].pos, _items[0].size)) {
		if (_items[0].state == ON) {
			_items[0].state = OFF;
			_musicManager->pauseMusic(id);
			_rend->remove2D(_items[0].soundOn);
			_rend->load2D(_items[0].soundOff, _items[0].pos);
		}
		else {
			_rend->remove2D(_items[0].soundOff);
			_items[0].state = ON;
			_musicManager->playMusic(id);
			_rend->load2D(_items[0].soundOn, _items[0].pos);
		}
	}
}

ids::IScene::sceneId ids::menu::Settings::run()
{
	setWindow();
	for (auto &item : _items) {
		_rend->load2D(item.soundOn, item.pos);
	}
	while (_rend->isRunning() && _id == SETTINGS) {
		if (_events.isKeyDown(irr::KEY_ESCAPE)) {
			_id = ids::IScene::QUIT;
			return _id;
		}
		auto mousePos = _events.getMousePosition();
		// _rend->isKeyPressed(irr::KEY_LBUTTON)
		computeEvent(mousePos);
		itemEvent();
		_rend->render();
	}
	return _id;
}