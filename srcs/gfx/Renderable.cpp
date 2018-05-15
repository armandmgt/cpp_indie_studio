/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Renderable
*/

#include "gfx/Renderable.hpp"

void gfx::Renderable::pushOnScreen()
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

void gfx::Renderable::setMesh(std::string const &filename)
{

}

vec3d<float> gfx::Renderable::getPosition() const
{
	return vec3d<float>(0, 0, 0);
}

void gfx::Renderable::render()
{

}

void gfx::Renderable::setPosition(vec3d<float> const &position)
{

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
