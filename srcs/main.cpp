/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <iostream>
#include "settingManager/settingManager.hpp"
#include "gfx/Renderer.hpp"

int main()
{
	std::string filename("../../settings/settings.xml");
	irr::core::stringw assetPath("/home/zombre/tek2/cpp_indie_studio/assets/meshs/ground.obj");
	gfx::Renderer window;
	vec3d<float> position(10.f, 100.f, 0.f);
	vec3d<float> positionlego(10,3,0);
	vec3d<float> size(0.f, 0.f, 0.f);
	vec3d<float> rotation(45.f, 0.f, 0.f);

	irr::core::array<irr::SJoystickInfo> joystickInfo;

	gfx::idSprite id;
	position = {0,0,0};
	id = window.createb3dMesh("/home/zombre/tek2/cpp_indie_studio/assets/meshs/perso.b3d");
	window.setPosition(id, positionlego);
	id = window.createMesh(assetPath);
	window.setPosition(id, positionlego);
	while (window.isRun()) {
		if (window.pollEvent() == ids::QUIT) {
			break;
		}
		window.render();
	}
	return 0;
}