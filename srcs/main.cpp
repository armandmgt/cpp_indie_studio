/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <iostream>
#include <settingManager/settingManager.hpp>
#include "menu/Launch.hpp"
#include "menu/Settings.hpp"
#include "gfx/Renderer.hpp"

int main()
{
	gfx::Renderer window;
	vec2d<int> pos(0,0);
	bool check = false;
	auto old = ids::IScene::PAUSE;
	auto state = ids::IScene::MENU;

	ids::menu::AMenu *testmenu;
	testmenu = new ids::menu::Launch(&window);
	while (window.isRun() && window.pollEvent() != ids::QUIT) {
		vec2d<int> mousePos = window.getMousePosition();
		testmenu->computeEvent(mousePos);
		state = testmenu->getSceneId();
		if (state != old) {
			switch (state) {
				case ids::IScene::QUIT:
					return 0;
				case ids::IScene::SETTINGS:
					delete testmenu;
					testmenu = new ids::menu::Settings(&window);
					break;
				case ids::IScene::MENU:
					delete testmenu;
					testmenu = new ids::menu::Launch(&window);
			}
		}
		old = state;
		window.render();
	}
	return 0;
}
