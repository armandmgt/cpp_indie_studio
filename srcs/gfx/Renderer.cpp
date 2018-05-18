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
	gfx::MyEventReceiver::SMouseState mouse =  Event.GetMouseState();
	vec2d<int> position(mouse.position.X, mouse.position.Y);

	return position;
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

void gfx::Renderer::newScene()
{

}

irr::scene::ISceneManager *gfx::Renderer::getScene()
{
	return smgr;
}

void gfx::Renderer::addArchive(std::string const &filename)
{
	device->getFileSystem()->addFileArchive(filename.c_str());
}

void gfx::Renderer::clear()
{
	smgr->clear();
}

int main()
{
	gfx::Renderer window;
	gfx::Renderable asset;

	window.addArchive("../../assets/meshs/map-20kdm2.pk3");
	asset.setMesh(window.getScene(), "20kdm2.bsp");
	asset.setPosition(vec3d<float>(0,0,0));
	while (window.isRun()) {
		if (window.pollEvent() == ids::QUIT) {
			return 0;
		}
		window.clear();
		window.render();
	}
}