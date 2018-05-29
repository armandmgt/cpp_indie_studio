/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Renderable
*/

#include <iostream>
#include "gfx/Renderer.hpp"

//TODO Sound

gfx::Renderer::Renderer() noexcept

{
	irr::core::stringw tittleWindow = "Bomberman";

	device = irr::createDevice(irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(1920, 1080), 1024, true, true,
				   false, &Event);
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	smgr->addCameraSceneNodeFPS();
	device->setWindowCaption(tittleWindow.c_str());
	guienv = device->getGUIEnvironment();
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
	guienv->drawAll();
	driver->enableMaterial2D();
	for (auto &image : images) {
		driver->draw2DImage(image.image,
				    {image.position.x, image.position.y}, image.size);
	}
	driver->enableMaterial2D(false);
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

void gfx::Renderer::newScene()
{
}

irr::scene::ISceneManager *gfx::Renderer::getScene()
{
	return smgr;
}

void gfx::Renderer::addArchive(irr::core::stringw const &filename)
{
	device->getFileSystem()->addFileArchive(filename);
}

void gfx::Renderer::clearScene()
{
	smgr->clear();
}

//TODO Problem to display the text
void
gfx::Renderer::drawText(vec2d<int> const &v, std::string const &text, bool fillBackground)
{
	guienv->addStaticText(L"coucocou", irr::core::rect<irr::s32>(v.x,v.y,260,22), fillBackground);
}

void gfx::Renderer::load2D(irr::core::stringw const &filename, vec2d<int> &positon,
			   irr::core::rect<irr::s32> &size)
{
	irr::video::ITexture *text = driver->getTexture(filename);

	images.emplace_back(text, positon, size);
}

void gfx::Renderer::load2D(irr::core::stringw const &filename, vec2d<int> &positon)
{
	irr::core::rect<irr::s32> size;
	irr::video::ITexture *text = driver->getTexture(filename);
	irr::core::vector2d<int> pos(0, 0);
	irr::core::vector2d<int> pos2(text->getOriginalSize().Width,
				      text->getOriginalSize().Height);
	size.UpperLeftCorner = pos;
	size.LowerRightCorner = pos2;
	driver->makeColorKeyTexture(text, irr::core::position2d<irr::s32>(0,0));
	images.emplace_back(text, positon, std::move(size));
}

irr::video::IVideoDriver *gfx::Renderer::getDriver()
{
	return driver;
}


