/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** GameContainer
*/

#include "engine/GameContainer.hpp"

ids::GameContainer::GameContainer()
{
	device = irr::createDevice(
		irr::video::EDT_SOFTWARE,
		irr::core::dimension2d<irr::u32>(640, 480), 16, false,
		false, false, nullptr);

	if (!device)
		return;
	device->setWindowCaption(L"Hello World!");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		irr::core::rect<irr::s32>(10,10,260,22), true);
	smgr->addCameraSceneNode(nullptr, irr::core::vector3df(0,30,-40),
		irr::core::vector3df(0,5,0));
}

ids::GameContainer *ids::GameContainer::create()
{
	return new GameContainer();
}

void ids::GameContainer::start()
{
	while(device->run()) {
		driver->beginScene(true, true,
			irr::video::SColor(255,100,101,140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}
}

ids::GameContainer::~GameContainer()
{
	device->drop();
}
