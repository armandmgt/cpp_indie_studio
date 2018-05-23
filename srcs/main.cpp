/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <string>
#include <iostream>
#include <settingManager/settingManager.hpp>
#include "gfx/Renderable.hpp"
#include "gfx/Renderer.hpp"

int main()
{
	std::string filename("../../settings/settings.xml");
	gfx::Renderer window;
	gfx::Renderable asset;
	opt::settingManager settings(filename);

	settings.load();
//	window.addArchive(settings.getValue("archive"));
//	asset.setMesh(window.getScene(), settings.getValue("mesh"));
//	asset.setPosition(vec3d<float>(-1300,-144,-1249));
	window.load2D("../../assets/textures/texture.jpg");
	while (window.isRun()) {
		if (window.pollEvent() == ids::QUIT) {
			break;
		}
		window.render();
	}
	return 0;
}