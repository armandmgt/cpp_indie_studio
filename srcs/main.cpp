/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <iostream>
#include "settingManager/settingManager.hpp"
#include "gfx/Renderer.hpp"

static void createGround(size_t xSize, size_t zSize,
	const irr::core::stringw &assetPath, gfx::Renderer &renderer
);

int main()
{
	irr::core::stringw assetPath("../../assets/meshs/ground.obj");
	gfx::Renderer window;
	vec3d<float> position(10.f, 100.f, 0.f);
	vec3d<float> positionlego(10, 0, 10);
	vec3d<float> size(0.f, 0.f, 0.f);
	vec3d<float> rotation(45.f, 0.f, 0.f);

	gfx::idSprite id;
	position = {0,0,0};
//	id = window.createb3dMesh("../../assets/meshs/perso.b3d");
//	window.setPosition(id, positionlego);
	createGround(21, 20, assetPath, window);
	while (window.isRun()) {
		auto event = window.pollEvent();
		if (event == ids::QUIT) {
			break;
		}
		window.render();
	}
	return 0;
}

static void createGround(size_t xSize, size_t zSize,
	irr::core::stringw const &assetPath, gfx::Renderer &renderer)
{
	vec3d<float> pos{0, 0, 0};

	for (size_t x = 0; x < xSize; x++) {
		vec3d<float> size(0,0,0);
		for (size_t z = 0; z < zSize; z++) {
			gfx::idSprite id;
			if (id = renderer.createMesh(assetPath); id == -1) {
				return;
			}
			renderer.setPosition(id, pos);
			size = renderer.getSizeMesh(id);
			pos.z += size.z;
		}
		pos.z = 0;
		pos.x += size.x;
	}
}