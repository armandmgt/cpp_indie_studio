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

int main() {
	gfx::Renderer window;
	vec2d<int> pos(0, 0);
	bool check = false;
	auto state = ids::IScene::MENU;

	ids::menu::AMenu *testmenu;
	while (true) {
		switch (state) {
			case ids::IScene::MENU:
				delete testmenu;
				testmenu = new ids::menu::Launch(&window);
				state = testmenu->runPage();
				printf("after menu %d", state);
				break;
			case ids::IScene::QUIT:
				delete testmenu;
				exit(0);
			case ids::IScene::SETTINGS:
				delete testmenu;
				testmenu = new ids::menu::Settings(&window);
				state = testmenu->runPage();
				printf("after settings\n");
				break;
		}
		//window.render();
	}
	//}
	return 0;
}
