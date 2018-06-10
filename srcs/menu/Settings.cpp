/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Settings
*/

#include "menu/Settings.hpp"

ids::menu::Settings::Settings(std::shared_ptr<gfx::Renderer> rend) : AMenu(rend, SETTINGS), _events{rend->getEventReceiver()},
	_music{ON},
	_items{
		{"Sound", ON, "../assets/menu/volume.png", "../assets/menu/mute.png", {928, 510}},
		{"Board", NONE, "../assets/menu/Items/score-board.png", "../assets/menu/Items/score-board.png",
			{480, 180}}
	}
{
	_infoButtons = {
		{{480,1000}, {107,55}, "../assets/menu/buttons/default/play-button.png",
			"../assets/menu/buttons/active/a-play-button.png", GAME, false},
		{{750,1000}, {195,53}, "../assets/menu/buttons/default/scores-button.png",
			"../assets/menu/buttons/active/a-scores-button.png", SCORE, false},
		{{1100,1000}, {143,53}, "../assets/menu/buttons/default/back-button.png",
			"../assets/menu/buttons/active/a-back-button.png", MENU, false},
		{{1400,1000}, {101,63}, "../assets/menu/buttons/default/quit-button.png",
			"../assets/menu/buttons/active/a-quit-button.png", QUIT, false}
	};
	_backgroundImg = "../assets/menu/background/background-default.png";
}

ids::menu::Settings::~Settings()
{
	_rend->clearScene();
}

void ids::menu::Settings::settingsItems()
{
	//_mousePos
}

void ids::menu::Settings::setMusicLevel()
{

}

ids::IScene::sceneId ids::menu::Settings::run()
{
	setWindow();
	for (auto &item : _items) {
		_rend->load2D(item.soundOn, item.pos);
	}
	settingsItems();
	while (_rend->isRunning() && _id != MENU && _id != QUIT) {
		if (_events.isKeyDown(irr::KEY_ESCAPE)) {
			_id = ids::IScene::QUIT;
			return _id;
		}
		auto mousePos = _events.getMousePosition();
		// _rend->isKeyPressed(irr::KEY_LBUTTON)
		computeEvent(mousePos);
		_rend->render();
	}
	return _id;
}