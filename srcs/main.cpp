/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <iostream>
#include "engine/GameContainer.hpp"

int main()
{
	try {
		ids::GameContainer gc;
		gc.start();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 84;
	}
	return 0;
}

//	Map map(22, 20);
//	map.initMap(20);
//	map.printMap();
//	gfx::Renderer renderer;
//	ecs::World ecs(&renderer);
//	ecs.createGround(22, 20, "assets/meshs/ground.obj");
//	ids::Event event(renderer);
//	irr::EKEY_CODE key;
//	ids::event_t ev{};
//	std::chrono::steady_clock::time_point timer = std::chrono::steady_clock::now();
//
//	ecs._spawnEntitiesFromMap(std::move(map.getMap()));
//	ecs.drawEntities();
//	while (renderer.isRunning()) {
//		if (event.pollEvent(key, ev)) {
//			if (ev.value.key == ids::ESCAPE)
//			renderer.close();
//		}
//		auto now = std::chrono::steady_clock::now();
//		auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - timer);
//		if (delta.count() > (1000 / 60)) {
//			ecs.update(delta.count());
//		}
//		renderer.render();
//	}
//	return 0;

