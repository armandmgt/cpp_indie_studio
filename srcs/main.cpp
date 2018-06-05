/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <string>
#include <iostream>
#include <memory>
#include <event/Event.hpp>
#include "settingManager/settingManager.hpp"
#include "gfx/Renderer.hpp"
#include "world/World.hpp"

int main()
{
	Map map(22, 20);
	map.initMap(20);
	map.printMap();
	gfx::Renderer renderer;
	ecs::world ecs(renderer);
	auto node = renderer.createElem("../../assets/meshs/max-bomb.obj");
	renderer.setPosition(node, {10, 0, 10});
	ecs.createGround(22, 20, "../../assets/meshs/ground.obj");
	ids::Event event(renderer);
	irr::EKEY_CODE key;
	ids::event_t ev{};

	ecs._spawnEntitiesFromMap(std::move(map.getMap()));
	ecs.drawEntities();
	float z = 0;
	while (renderer.isRunning()) {
		if (event.pollEvent(key, ev)) {
			if (ev.value.key == ids::ESCAPE)
			renderer.close();
		}
		renderer.rotate(node, {0, z++, 0});
		renderer.render();
	}
	// ecs.debug();
	return 0;
}
