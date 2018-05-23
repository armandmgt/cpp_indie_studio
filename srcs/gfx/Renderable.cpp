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
		positions = setposition;
		node->setPosition(irr::core::vector3df(positions.x,
						       positions.y,
						       positions.z));
	}
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

