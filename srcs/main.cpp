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
	ecs.createGround(22, 20, "../../assets/meshs/ground.obj");
	ids::Event event(renderer);
	irr::EKEY_CODE key;
	ids::event_t ev{};

	ecs._spawnEntitiesFromMap(std::move(map.getMap()));
	ecs.drawEntities();
	while (renderer.isRunning()) {
		if (event.pollEvent(key, ev)) {
			if (ev.value.key == ids::ESCAPE)
			renderer.close();
		}
		size_t i = 0;
		for (auto &entity : ecs._world) {
			if (entity.hasComponent<ecs::Character>()) {
				std::cout << "Character at index " << i << std::endl;
				ecs.systemSpawnBomb(i);
			}
			i++;
		}
		renderer.render();
	}
	return 0;
}
