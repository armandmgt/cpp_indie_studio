/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Renderable
*/

#include <iostream>
#include "gfx/Renderable.hpp"

gfx::Renderable::Renderable() : positions(0.0, 0.0, 0.0)
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

void gfx::Renderable::setMesh(irr::scene::ISceneManager *scene, std::string const &filename)
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
		node->setPosition(irr::core::vector3df(setposition.x,
						       setposition.y,
						       setposition.z));
		positions.x = setposition.x;
		positions.y = setposition.y;
		positions.z = setposition.z;
	}
}

void gfx::Renderable::playAnimation(AnimationType type) const
{

}

bool gfx::Renderable::is3D() const
{
	return false;
}

bool gfx::Renderable::isAnimable() const
{
	return false;
}

