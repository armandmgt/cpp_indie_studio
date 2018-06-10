/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** LoadGame
*/

#include "menu/LoadGame.hpp"

ids::menu::LoadGame::LoadGame(gfx::Renderer *rend, ids::Music *music) :
	AMenu(rend, LOAD, music), _events{rend->getEventReceiver()},
	_items{
		{"../assets/menu/trollol/trollol.png", {480, 100}, {991, 806}},
		{"../assets/menu/trollol/trollol2.png", {480,100}, {991, 806}},
		{"../assets/menu/trollol/trollol3.png", {480,100}, {991, 806}},
		{"../assets/menu/trollol/trollol4.png", {480,100}, {991, 806}},
		{"../assets/menu/trollol/trollol5.png", {480,100}, {991, 806}},
	},
	_itemIndex(0)
{
	_infoButtons = {
		{{700,1000}, {107,55}, "../assets/menu/buttons/default/play-button.png",
			"../assets/menu/buttons/active/a-play-button.png", GAME, false},
		{{930,1000}, {143,53}, "../assets/menu/buttons/default/back-button.png",
			"../assets/menu/buttons/active/a-back-button.png", MENU, false},
		{{1200,1000}, {101,63}, "../assets/menu/buttons/default/quit-button.png",
			"../assets/menu/buttons/active/a-quit-button.png", QUIT, false}
	};
	_backgroundImg = "../assets/menu/background/background-default.png";
}

ids::menu::LoadGame::~LoadGame()
{
	_rend->clearScene();
}

void	ids::menu::LoadGame::itemEvent()
{
	if (_mouseData.leftButtonDown && insideRect(_items[_itemIndex].pos,
						    _items[_itemIndex].size)) {
		_itemIndex++;
		if (_itemIndex >= _items.size()) {
			_itemIndex = 0;
		}
		_rend->load2D(_items[_itemIndex].path, _items[_itemIndex].pos);

	}
}

ids::IScene::sceneId ids::menu::LoadGame::run()
{
	setWindow();
	_rend->load2D(_items[_itemIndex].path, _items[_itemIndex].pos);
	while (_rend->isRunning() && _id == LOAD) {
		if (_events.isKeyDown(irr::KEY_ESCAPE)) {
			_id = ids::IScene::QUIT;
			return _id;
		}
		_mouseData = _events.getMousePosition();
		buttonEvent();
		itemEvent();
		_rend->render();
	}
	return _id;
}