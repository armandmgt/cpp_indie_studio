/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Renderable
*/

#include <iostream>
#include "gfx/Renderer.hpp"
#include "irrlicht/driverChoice.h"

gfx::Renderer::Renderer() : _id(0)

{
	irr::core::stringw tittleWindow = "Bomberman";

	if (device = irr::createDevice(irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(1920, 1080), 1024, true, true,
		false, &Event); !device)
		throw std::exception();
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	//smgr->addCameraSceneNodeFPS();
	device->setWindowCaption(tittleWindow.c_str());
	guienv = device->getGUIEnvironment();
	auto light = smgr->addLightSceneNode(nullptr,
		irr::core::vector3df{0, 300, -190},
		irr::video::SColorf{.7, .7, .3, 0}, 500.f);
	irr::scene::IBillboardSceneNode* bill = smgr->addBillboardSceneNode(
		light, irr::core::dimension2d<irr::f32>(10, 10));
	bill->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	bill->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	bill->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	light->setDebugDataVisible(irr::scene::EDS_FULL);
}

gfx::Renderer::~Renderer()
{
	device->drop();
}

bool gfx::Renderer::isRun() const
{
	return device->run();
}

void gfx::Renderer::render()
{
	driver->beginScene(true, true, irr::video::SColor(255, 113, 113, 113));
	smgr->drawAll();
	guienv->drawAll();
	driver->enableMaterial2D();
	for (auto &image : images) {
		driver->draw2DImage(image.image,
				    {image.position.x, image.position.y}, image.size , 0, irr::video::SColor(255,255,255,255), true);
	}
	driver->enableMaterial2D(false);
	//images.back().image->drop();
	//images.pop_back();
	driver->endScene();
}

void gfx::Renderer::clearScene()
{
	smgr->clear();
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
		{irr::KEY_ESCAPE, ids::QUIT},
		{irr::KEY_LEFT, ids::LEFT},
		{irr::KEY_RIGHT, ids::RIGHT},
		{irr::KEY_UP, ids::UP},
		{irr::KEY_DOWN, ids::DOWN}
	};

	for (auto &it : binding) {
		if (Event.IsKeyDown(it.first))
			return it.second;
	}
	return ids::NONE;
}

void gfx::Renderer::addArchive(irr::core::stringw const &filename)
{
	device->getFileSystem()->addFileArchive(filename);
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

gfx::idSprite gfx::Renderer::createMesh(irr::core::stringw const &filename)
{
	irr::scene::IAnimatedMesh *mesh;
	irr::scene::IAnimatedMeshSceneNode *aniMesh;

	if (mesh = smgr->getMesh(filename.c_str()); !mesh) {
		return -1;
	} else if (aniMesh = smgr->addAnimatedMeshSceneNode(mesh); !aniMesh) {
		return -1;
	} else {
		meshs.push_back(mesh);
		animatedMeshs.push_back(aniMesh);
		aniMesh->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,
			false);
		return animatedMeshs.size() - 1;
	}
}

bool gfx::Renderer::addTexture(gfx::idSprite id, std::string filename)
{
	return false;
}

bool gfx::Renderer::setAnimationSpeed(gfx::idSprite id, float speed)
{
	if (animatedMeshs[id]) {
		animatedMeshs[id]->setAnimationSpeed(speed);
		return true;
	}
	return false;
}

bool gfx::Renderer::setPosition(gfx::idSprite id, vec3d<float> position)
{
	if (animatedMeshs[id]) {
		animatedMeshs[id]->setPosition({position.x,
					       position.y,
					       position.z});
		return true;
	}
	return false;
}

bool gfx::Renderer::rotateMesh(gfx::idSprite id, vec3d<float> angle)
{
	if (animatedMeshs[id]) {
		animatedMeshs[id]->setRotation({angle.x,
					       angle.y,
					       angle.z});
		return true;
	}
	return false;
}

vec3d<float> gfx::Renderer::getSizeMesh(gfx::idSprite id)
{
	irr::core::vector3df extent = animatedMeshs.at(id)->getTransformedBoundingBox().getExtent();
	return {extent.X, extent.Y, extent.Z};
}

gfx::idSprite gfx::Renderer::createb3dMesh(irr::core::stringw const &filename)
{
	irr::scene::IAnimatedMesh *mesh;
	irr::scene::IAnimatedMeshSceneNode *aniMesh;

	if (mesh = smgr->getMesh(filename.c_str()); !mesh) {
		return -1;
	} else if (aniMesh = smgr->addAnimatedMeshSceneNode(mesh); !aniMesh) {
		return -1;
	} else {
		meshs.push_back(mesh);
		animatedMeshs.push_back(aniMesh);
		aniMesh->getMaterial(0).NormalizeNormals = true;
		aniMesh->getMaterial(0).Lighting = true;
		aniMesh->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,
			false);
		return animatedMeshs.size() - 1;
	}
}


