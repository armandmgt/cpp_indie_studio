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
	irr::core::stringw groundFile("../../assets/meshs/ground.obj");
	irr::core::stringw characterFile("../../assets/meshs/ninja.b3d");
	gfx::Renderer window;
	vec3d<float> ninjaPos{10, 8, 10};
	irr::EKEY_CODE key;

	createGround(21, 20, groundFile, window);
	auto ninjaNode = window.createAnimatedElem(characterFile);
	if (ninjaNode != nullptr) {
		window.setScale(ninjaNode, 2.f);
		window.setPosition(ninjaNode, ninjaPos);
		window.rotate(ninjaNode, {0, 90, 0});
		window.addAnimation(ninjaNode, "walk", vec2d<int>{1, 12});
		window.setAnimationSpeed(ninjaNode, 14);
		window.setAnimation(ninjaNode, "walk");
	}
	while (window.isRun()) {
		window.render();
		if (!window.getKeyPressed(key)) {
			window.setAnimationSpeed(ninjaNode, 0);
			continue;
		}
		switch (key) {
		case irr::KEY_ESCAPE:
			window.close();
			break;
		case irr::KEY_KEY_A:
			ninjaPos.x -= 1;
			window.rotate(ninjaNode, {0, -90, 0});
			window.setAnimationSpeed(ninjaNode, 14);
			break;
		case irr::KEY_KEY_D:
			ninjaPos.x += 1;
			window.rotate(ninjaNode, {0, 90, 0});
			window.setAnimationSpeed(ninjaNode, 14);
			break;
		default:
			break;
		}
		window.setPosition(ninjaNode, ninjaPos);
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
			irr::scene::ISceneNode *node;
			if (!(node = renderer.createElem(assetPath))) {
				return;
			}
			renderer.setPosition(node, pos);
			size = renderer.getSize(node);
			pos.z += size.z;
		}
		pos.z = 0;
		pos.x += size.x;
	}
}