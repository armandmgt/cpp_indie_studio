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
	irr::core::stringw assetPath("/home/zombre/tek2/cpp_indie_studio/assets/meshs/ground.obj");
	gfx::Renderer window;
	vec3d<float> position(10.f, 100.f, 0.f);
	vec3d<float> positionlego(0,-3,30);
	vec3d<float> size(0.f, 0.f, 0.f);
	vec3d<float> rotation(45.f, 0.f, 0.f);

	gfx::idSprite id;
	position = {0,0,0};
	id = window.createb3dMesh("/home/zombre/tek2/cpp_indie_studio/assets/meshs/perso.b3d");
	window.setPosition(id, positionlego);
	//id = window.createMesh(assetPath);
	//window.setPosition(id, positionlego);
	while (window.isRun()) {
		auto event = window.pollEvent();
		if (event == ids::QUIT) {
			break;
		} else if (event == ids::LEFT) {
			positionlego.x = positionlego.x + 1;
			window.setPosition(id, positionlego);
		} else if (event == ids::RIGHT) {
			positionlego.x = positionlego.x - 1;
			window.setPosition(id, positionlego);
		} else if (event == ids::UP) {
			positionlego.z = positionlego.z + 1;
			window.setPosition(id, positionlego);
		} else if (event == ids::DOWN) {
			positionlego.z = positionlego.z - 1;
			window.setPosition(id, positionlego);
		}
		rotation.x = rotation.x + 1;
		rotation.y = rotation.y + 1;
		window.rotateMesh(id, rotation);
		window.render();
	}
	return 0;
}