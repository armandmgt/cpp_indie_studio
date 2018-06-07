/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Renderable
*/

#include "gfx/Renderer.hpp"

//TODO Sound

gfx::Renderer::Renderer()
{
	irr::core::stringw tittleWindow = "Bomberman";

	if (!(device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 1024,
		false, true, false, &eventReceiver)))
		throw std::runtime_error("Cannot get device");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	smgr->addCameraSceneNode();
	device->setWindowCaption(tittleWindow.c_str());
	guienv = device->getGUIEnvironment();
	auto light = smgr->addLightSceneNode(nullptr, irr::core::vector3df{100, 300, -190},
		irr::video::SColorf{1, 1, 1, 0}, 500.f);
	irr::scene::IBillboardSceneNode* bill = smgr->addBillboardSceneNode(
		light, irr::core::dimension2d<irr::f32>(10, 10));
	bill->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	bill->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	bill->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

gfx::Renderer::~Renderer()
{
	device->drop();
}

void gfx::Renderer::render()
{
	driver->beginScene(true, true, irr::video::SColor(255, 113, 113, 113));
	smgr->drawAll();
	guienv->drawAll();
	driver->enableMaterial2D();
	for (auto &image : images)
		driver->draw2DImage(image.texture, {image.position.x, image.position.y}, image.size, nullptr,
			irr::video::SColor(255,255,255,255), true);
	driver->enableMaterial2D(false);
	driver->endScene();
}

bool gfx::Renderer::isRunning() const
{
	return device->run();
}

void gfx::Renderer::clearScene()
{
	smgr->clear();
}

void gfx::Renderer::close()
{
	device->closeDevice();
}

vec2d<int> gfx::Renderer::getMousePosition() const
{
	const gfx::MyEventReceiver::SMouseState &mouse = eventReceiver.getMouseState();

	return {mouse.position.X, mouse.position.Y};
}

bool gfx::Renderer::getKeyPressed(irr::EKEY_CODE &keyCode) const
{
	for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++) {
		if (eventReceiver.isKeyDown(static_cast<irr::EKEY_CODE>(i))) {
			keyCode = static_cast<irr::EKEY_CODE>(i);
			return true;
		}
	}
	return false;
}

bool gfx::Renderer::isKeyPressed(irr::EKEY_CODE code)
{
	return eventReceiver.isKeyDown(code);
}

irr::scene::ISceneNode *gfx::Renderer::createElem(irr::core::stringw const &filename)
{
	irr::scene::IMesh *mesh = smgr->getMesh(filename);
	irr::scene::IMeshSceneNode *sceneNode;

	if (!mesh) {
		return nullptr;
	} else if (!(sceneNode = smgr->addMeshSceneNode(mesh))) {
		return nullptr;
	} else {
		sceneNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
//		sceneNode->setDebugDataVisible(irr::scene::EDS_NORMALS);
		return sceneNode;
	}
}

irr::scene::IAnimatedMeshSceneNode *gfx::Renderer::createAnimatedElem(irr::core::stringw const &filename)
{
	irr::scene::IAnimatedMesh *mesh;
	irr::scene::IAnimatedMeshSceneNode *sceneNode;

	if (!(mesh = smgr->getMesh(filename.c_str()))) {
		return nullptr;
	} else if (!(sceneNode = smgr->addAnimatedMeshSceneNode(mesh))) {
		return nullptr;
	} else {
		sceneNode->getMaterial(0).NormalizeNormals = true;
		sceneNode->getMaterial(0).Lighting = true;
		sceneNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
		return sceneNode;
	}
}

bool gfx::Renderer::addTexture(irr::scene::ISceneNode *node, const irr::core::stringw &filename)
{
	irr::video::ITexture *texture;

	if (!node)
		return false;
	if (!(texture = driver->getTexture(filename)))
		return false;
	node->setMaterialTexture(0, texture);
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	return true;
}

void gfx::Renderer::addAnimation(irr::scene::IAnimatedMeshSceneNode *node, const std::string &identifier,
	const vec2d<int> &range
)
{
	auto &nodeAnimations = animations[node];
	nodeAnimations[identifier] = range;
}

void gfx::Renderer::setAnimation(irr::scene::IAnimatedMeshSceneNode *node, const std::string &identifier)
{
	const auto &nodeAnimations = animations.at(node);
	const auto &animation = nodeAnimations.at(identifier);
	node->setFrameLoop(animation.x, animation.y);
}

bool gfx::Renderer::setAnimationSpeed(irr::scene::IAnimatedMeshSceneNode *node, float speed)
{
	if (!node)
		return false;
	node->setAnimationSpeed(speed);
	return true;
}

bool gfx::Renderer::setPosition(irr::scene::ISceneNode *node, const vec3d<float> &pos)
{
	if (!node)
		return false;
	node->setPosition({pos.x, pos.y, pos.z});
	return true;
}

bool gfx::Renderer::setScale(irr::scene::ISceneNode *node, float scale)
{
	if (!node)
		return false;
	node->setScale(irr::core::vector3df(scale));
	return true;
}

bool gfx::Renderer::rotate(irr::scene::ISceneNode *node, const vec3d<float> &angle)
{
	if (!node)
		return false;
	node->setRotation({angle.x, angle.y, angle.z});
	return true;
}

vec3d<float> gfx::Renderer::getSize(irr::scene::ISceneNode *node)
{
	irr::core::vector3df extent = node->getTransformedBoundingBox().getExtent();
	return {extent.X, extent.Y, extent.Z};
}

void gfx::Renderer::load2D(irr::core::stringw const &filename, const vec2d<int> &pos,
	const irr::core::rect<irr::s32> &rect
)
{
	irr::video::ITexture *texture;

	if (!(texture = driver->getTexture(filename)))
		throw std::runtime_error("Cannot load texture");
	images.emplace_back(texture, pos, rect);
}

void gfx::Renderer::load2D(irr::core::stringw const &filename, const vec2d<int> &pos)
{
	irr::video::ITexture *texture;
	if (!(texture = driver->getTexture(filename)))
		throw std::runtime_error("Cannot load texture");
	const irr::core::dimension2d<irr::u32> &texSize = texture->getOriginalSize();
	irr::core::rect<irr::s32> size{{0, 0},
		{static_cast<irr::s32>(texSize.Width), static_cast<irr::s32>(texSize.Height)}};
	images.emplace_back(texture, pos, std::move(size));
}

void gfx::Renderer::addArchive(irr::core::stringw const &filename)
{
	device->getFileSystem()->addFileArchive(filename);
}
