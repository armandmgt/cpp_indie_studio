/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <string>
#include <iostream>
#include <memory>
#include "settingManager/settingManager.hpp"
#include "gfx/Renderer.hpp"
#include "engine/GameContainer.hpp"
#include "world/World.hpp"

int main()
{
	Map map(22, 20);
	map.initMap(20);
	map.printMap();
	gfx::Renderer renderer;
	ecs::world ecs(renderer);
	ecs.createGround(22, 20, "../../assets/meshs/ground.obj");
	irr::EKEY_CODE key;
	ecs._spawnEntitiesFromMap(std::move(map.getMap()));
	ecs.drawEntities();
	while (renderer.isRunning()) {
		if (renderer.getKeyPressed(key) && key == irr::KEY_ESCAPE)
			renderer.close();
		renderer.render();
	}
	// ecs.debug();
	return 0;
}
/*
	irr::core::stringw groundFile("../../assets/meshs/ground.obj");
	irr::core::stringw characterFile("../../assets/meshs/ninja.b3d");
vec3d<float> ninjaPos{10, 8, 10};
irr::EKEY_CODE key;

createGround(21, 20, groundFile, renderer);
auto ninjaNode = renderer.createAnimatedElem(characterFile);
if (ninjaNode != nullptr) {
renderer.setScale(ninjaNode, 2.f);
renderer.setPosition(ninjaNode, ninjaPos);
renderer.rotate(ninjaNode, {0, 90, 0});
renderer.addAnimation(ninjaNode, "walk", vec2d<int>{1, 12});
renderer.setAnimationSpeed(ninjaNode, 14);
renderer.setAnimation(ninjaNode, "walk");
}
while (renderer.isRunning()) {
renderer.render();
if (!renderer.getKeyPressed(key)) {
renderer.setAnimationSpeed(ninjaNode, 0);
continue;
}
switch (key) {
case irr::KEY_ESCAPE:
renderer.close();
break;
case irr::KEY_KEY_A:
ninjaPos.x -= 1;
renderer.rotate(ninjaNode, {0, -90, 0});
renderer.setAnimationSpeed(ninjaNode, 14);
break;
case irr::KEY_KEY_D:
ninjaPos.x += 1;
renderer.rotate(ninjaNode, {0, 90, 0});
renderer.setAnimationSpeed(ninjaNode, 14);
break;
default:
break;
}
renderer.setPosition(ninjaNode, ninjaPos);
}
*/
