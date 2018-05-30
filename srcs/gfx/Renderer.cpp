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
	irr::SKeyMap keyMap[8];
	 keyMap[0].Action = irr::EKA_MOVE_FORWARD;
	 keyMap[0].KeyCode = irr::KEY_UP;
	 keyMap[1].Action = irr::EKA_MOVE_FORWARD;
	 keyMap[1].KeyCode = irr::KEY_KEY_W;

	 keyMap[2].Action = irr::EKA_MOVE_BACKWARD;
	 keyMap[2].KeyCode = irr::KEY_DOWN;
	 keyMap[3].Action = irr::EKA_MOVE_BACKWARD;
	 keyMap[3].KeyCode = irr::KEY_KEY_S;

	 keyMap[4].Action = irr::EKA_STRAFE_LEFT;
	 keyMap[4].KeyCode = irr::KEY_LEFT;
	 keyMap[5].Action = irr::EKA_STRAFE_LEFT;
	 keyMap[5].KeyCode = irr::KEY_KEY_A;

	 keyMap[6].Action = irr::EKA_STRAFE_RIGHT;
	 keyMap[6].KeyCode = irr::KEY_RIGHT;
	 keyMap[7].Action = irr::EKA_STRAFE_RIGHT;
	 keyMap[7].KeyCode = irr::KEY_KEY_D;
	smgr->addCameraSceneNode(nullptr, 100.f, 0.4f, -1, keyMap, 8);
	device->setWindowCaption(tittleWindow.c_str());
	guienv = device->getGUIEnvironment();
	smgr->addLightSceneNode(nullptr, {0, 20, 0}, {1.f, 1.f, 1.f}, 200.f);
	smgr->addSphereSceneNode(1.f, 16, nullptr, -1, {0,0,0}, {255,228,181});
	smgr->addSphereSceneNode(1.f, 16, nullptr, -1, {10,0,0}, {255,0,0});
	smgr->addSphereSceneNode(1.f, 16, nullptr, -1, {0,10,0}, {0,0,255});
	smgr->addSphereSceneNode(1.f, 16, nullptr, -1, {0,0,10}, {0,255,0});
	smgr->addSphereSceneNode(5.f, 16, nullptr, -1, {0,10,-5});
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
		driver->draw2DImage(image.image, {image.position.x, image
			.position.y}, image.size);
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
		{irr::KEY_ESCAPE, ids::QUIT},
		{irr::KEY_KEY_D, ids::LEFT},
		{irr::KEY_KEY_Q, ids::RIGHT},
		{irr::KEY_KEY_Z, ids::UP},
		{irr::KEY_KEY_S, ids::DOWN}
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
	animatedMeshs.push_back(smgr->addAnimatedMeshSceneNode(meshs.back()));
	auto const &aniMesh = animatedMeshs.back();
	aniMesh->setScale(irr::core::vector3df(10));
	aniMesh->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
	return animatedMeshs.size() - 1;
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
	animatedMeshs.push_back(smgr->addAnimatedMeshSceneNode(meshs.back()));
	auto const &aniMesh = animatedMeshs.back();
	aniMesh->setAnimationSpeed(8.f);
	aniMesh->getMaterial(0).NormalizeNormals = true;
	aniMesh->getMaterial(0).Lighting = true;
	aniMesh->setScale(irr::core::vector3df(9));
	return animatedMeshs.size() - 1;
}


