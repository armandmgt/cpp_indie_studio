/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <iostream>
#include <settingManager/settingManager.hpp>
#include "gfx/Renderable.hpp"
#include "menu/Launch.hpp"

int main()
{
	std::string filename("../../settings/settings.xml");
	gfx::Renderer window;
	gfx::Renderable asset;
	opt::settingManager settings(filename);
	vec2d<int> pos(0,0);
	irr::core::rect<irr::s32> size(0,0,1920, 1080);

	settings.load();
//	window.addArchive(settings.getValue("archive"));
//	asset.setMesh(window.getScene(), settings.getValue("mesh"));
//	asset.setPosition(vec3d<float>(-1300,-144,-1249));
	ids::menu::Launch testmenu(&window);
	while (window.isRun()) {
		if (window.pollEvent() == ids::QUIT) {
			break;
		}
		vec2d<int> mousePos = window.getMousePosition();
		testmenu.computeEvent(mousePos);
		window.render();
		switch (testmenu.getSceneId()) {
			case ids::IScene::QUIT:
				return 0;
				break;
			default:
				break;
		}
	}
	return 0;
}