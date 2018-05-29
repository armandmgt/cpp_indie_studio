/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <string>
#include <iostream>
#include "settingManager/settingManager.hpp"
#include "gfx/Renderable.hpp"
#include "gfx/Renderer.hpp"

int main()
{
	std::string filename("../../settings/settings.xml");
	gfx::Renderer window;
	gfx::Renderable asset;
	opt::settingManager settings(filename);
	vec2d<int> pos(0,0);
	irr::core::rect<irr::s32> size(0,0,100,500);

	settings.load();
	window.addArchive(settings.getValue("archive"));
	//asset.setMesh(window.getScene(), settings.getValue("mesh"))
	asset.setAnimatedMesh(window.getScene(), "../../assets/meshs/ground.obj");
	asset.setPosition(vec3d<float>(150, 150, 150));
	while (window.isRun()) {
		if (window.pollEvent() == ids::QUIT) {
			break;
		}
		window.render();
	}
	return 0;
}