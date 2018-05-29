/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Renderable
*/

#include <iostream>
#include "gfx/Renderable.hpp"

gfx::Renderable::Renderable() : positions(0.0, 0.0, 0.0),
				mesh(nullptr),
				animatedMesh(nullptr),
				node(nullptr),
				meshSet(false)
{
}


void gfx::Renderable::removeFromScreen()
{

}

void gfx::Renderable::setAnimation(AnimationType type,
				 std::string const &filename)
{

}

void gfx::Renderable::setTexture(std::string const &filename)
{

}

void gfx::Renderable::setMesh(irr::scene::ISceneManager *scene, irr::core::stringw const &filename)
{
	mesh = scene->getMesh(filename.c_str());
	if (mesh) {
		node = scene->addOctreeSceneNode(mesh->getMesh(0), nullptr, -1,
						 1024);
	}
}

void gfx::Renderable::setAnimatedMesh(irr::scene::ISceneManager *scene, irr::core::stringw const &filename)
{
	mesh = scene->getMesh(filename.c_str());
	animatedMesh = scene->addAnimatedMeshSceneNode(mesh);
	if (animatedMesh) {
		animatedMesh->setAnimationSpeed(8.f);
	}
}

vec3d<float> gfx::Renderable::getPosition() const
{
	return positions;
}

void gfx::Renderable::render()
{
}

void gfx::Renderable::setPosition(vec3d<float> const &setposition)
{
	if (node) {
		node->setPosition(irr::core::vector3df(positions.x,
						       positions.y,
						       positions.z));
	}
	if (animatedMesh) {
		animatedMesh->setPosition((irr::core::vector3df(positions.x,
								positions.y,
								positions.z)));
	}
	positions = setposition;
}

void gfx::Renderable::playAnimation(AnimationType type) const
{

}

bool gfx::Renderable::is3D() const
{
	return meshSet;
}

bool gfx::Renderable::isAnimable() const
{
	return false;
}

void gfx::Renderable::setTextureonMesh(irr::core::stringw const &filename,
				       irr::video::IVideoDriver *driver) {

	if (animatedMesh) {
		animatedMesh->setMaterialTexture(0, driver->getTexture(filename.c_str()));
	}
}

