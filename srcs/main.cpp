/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** main
*/

#include <string>
#include <iostream>
#include <memory>
#include <chrono>
#include "event/Event.hpp"
#include "settingManager/settingManager.hpp"
#include "gfx/Renderer.hpp"
#include "world/World.hpp"

int main()
{
	Map map(22, 20);
	map.initMap(20);
	map.printMap();
	gfx::Renderer renderer;
	ecs::World ecs(&renderer);
	ecs.createGround(22, 20, "assets/meshs/ground.obj");
	ids::Event event(renderer);
	std::queue<ids::eventType> ev;
	std::chrono::steady_clock::time_point timer = std::chrono::steady_clock::now();

	ecs._spawnEntitiesFromMap(std::move(map.getMap()));
	ecs.drawEntities();
	while (renderer.isRunning()) {
		if (event.pollEvent()) {
			ev = event.getEvent(1);
			while (!ev.empty()) {
				if (ev.back().key == ids::ESCAPE)
					renderer.close();
				ev.pop();
			}
		}
		auto now = std::chrono::steady_clock::now();
		auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - timer);
		if (delta.count() > (1000 / 60)) {
			ecs.update(delta.count());
		}
		renderer.render();
	}
	return 0;
}
