/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Renderable
*/

#include <iostream>
#include "gfx/Renderer.hpp"

gfx::Renderer::Renderer() noexcept : _id(0)

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
	smgr->addLightSceneNode(nullptr, irr::core::vector3df(10,100,0),
				irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);
	smgr->setShadowColor(irr::video::SColor(127,0,0,0));
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
		{irr::KEY_ESCAPE, ids::QUIT}
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
	meshs.push_back(smgr->getMesh(filename.c_str()));
	animatedMeshs.push_back(smgr->addAnimatedMeshSceneNode(meshs[_id]));
	animatedMeshs[_id]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	animatedMeshs[_id]->setMaterialType(irr::video::EMT_REFLECTION_2_LAYER);
	animatedMeshs[_id]->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
	animatedMeshs[_id]->setScale(irr::core::vector3df(2,2,2));
	animatedMeshs[_id]->addShadowVolumeSceneNode(nullptr, -1, true);
	animatedMeshs[_id]->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	return _id++;
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
	vec3d<float> size(0,0,0);
	auto *edges = new irr::core::vector3d<irr::f32>[8];
	auto boundingBox = animatedMeshs[id]->getTransformedBoundingBox();
	boundingBox.getEdges(edges);

	size.y = edges[1].Y - edges[0].Y;
	size.x = edges[5].X - edges[1].X;
	size.z = edges[2].Z - edges[0].Z;
	return size;
}

gfx::idSprite gfx::Renderer::createb3dMesh(irr::core::stringw const &file)
{
	meshs.push_back(smgr->getMesh(file.c_str()));
	animatedMeshs.push_back(smgr->addAnimatedMeshSceneNode(meshs[_id]));
	animatedMeshs[_id]->setAnimationSpeed(8.f);
	animatedMeshs[_id]->getMaterial(0).NormalizeNormals = true;
	animatedMeshs[_id]->getMaterial(0).Lighting = true;
	return _id++;
}


