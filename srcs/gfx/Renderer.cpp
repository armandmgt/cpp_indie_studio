/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Renderable
*/

#include <iostream>
#include "gfx/Renderer.hpp"

gfx::Renderer::Renderer()
{
	irr::core::stringw tittleWindow = "Bomberman";

	device = irr::createDevice(irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(1920, 1080), 16, true, true,
				   false, &Event);
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	smgr->addCameraSceneNodeFPS();
	device->setWindowCaption(tittleWindow.c_str());
}

gfx::Renderer::~Renderer()
{
	device->drop();
}

bool gfx::Renderer::isRun()
{
	return device->run();
}

void gfx::Renderer::render(std::vector<gfx::Renderable> &v)
{
	for (auto &it : v)
		it.render();
}

void gfx::Renderer::render()
{
	driver->beginScene(true, true, irr::video::SColor(255,255,255,255));
	smgr->drawAll();
	driver->endScene();
}

vec2d<int> gfx::Renderer::getMousePosition()
{
	return vec2d<int>(0, 0);
}

ids::eventKey gfx::Renderer::pollEvent()
{
	static mabBinding const binding = {
		{irr::KEY_ESCAPE, ids::QUIT}
	};

	for (auto &it : binding) {
		if (Event.IsKeyDown(it.first))
			return it.second;
	}
	return ids::NONE;
}

void gfx::Renderer::renderGameBoad()
{

}

int main()
{
	gfx::Renderer window;

	while (window.isRun()) {
		if (window.pollEvent() == ids::QUIT) {
			return 0;
		}
		window.render();
	}
}