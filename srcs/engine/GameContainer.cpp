/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** GameContainer
*/

#include "engine/GameContainer.hpp"

ids::GameContainer::GameContainer() : _ge()
{
	_device = irr::createDevice(
		irr::video::EDT_SOFTWARE,
		irr::core::dimension2d<irr::u32>(640, 480), 16, false,
		false, false, nullptr);

	if (!_device)
		return;
	_device->setWindowCaption(L"Hello World!");
	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_guienv = _device->getGUIEnvironment();
	_guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		irr::core::rect<irr::s32>(10,10,260,22), true);
	_smgr->addCameraSceneNode(nullptr, irr::core::vector3df(0,30,-40),
		irr::core::vector3df(0,5,0));
}

ids::GameContainer *ids::GameContainer::create()
{
	return new GameContainer();
}

void ids::GameContainer::start()
{
	while(_device->run()) {
		_driver->beginScene(true, true,
			irr::video::SColor(255,100,101,140));
		_smgr->drawAll();
		_guienv->drawAll();
		_driver->endScene();
	}
}

ids::GameContainer::~GameContainer()
{
	_device->drop();
}
