/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <iostream>
#include <settingManager/settingManager.hpp>
#include "menu/Launch.hpp"
#include "gfx/Renderer.hpp"

int main()
{
	//irr::core::stringw assetPath("../../assets/meshs/ground.obj");
	gfx::Renderer window;
	//opt::settingManager settings(filename);
	vec2d<int> pos(0,0);
	irr::core::rect<irr::s32> size(0,0,1920, 1080);

	//settings.load();
//	window.addArchive(settings.getValue("archive"));
//	asset.setMesh(window.getScene(), settings.getValue("mesh"));
//	asset.setPosition(vec3d<float>(-1300,-144,-1249));
	ids::menu::Launch testmenu(&window);
	while (window.isRun() && window.pollEvent() != ids::QUIT) {
		vec2d<int> mousePos = window.getMousePosition();
		testmenu.computeEvent(mousePos);
		switch (testmenu.getSceneId()) {
			case ids::IScene::QUIT:
				//delete &window;
				return 0;
			default:
				break;
		}
//		auto event = window.pollEvent();
//		if (event == ids::QUIT) {
//			break;
//		}
		window.render();
	}
	return 0;
}
