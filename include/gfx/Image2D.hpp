/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** image2D
*/
#ifndef CPP_INDIE_STUDIO_IMAGE2D_HPP
#define CPP_INDIE_STUDIO_IMAGE2D_HPP

#include <vector>
#include <irrlicht/ITexture.h>
#include "common/vec.hpp"

namespace gfx {
	class image2D {
	public:
		image2D(irr::video::ITexture *im, vec2d<int> &pos,
		irr::core::rect<irr::s32> sz) : image(im),
						 position(pos),
						 size(std::move(sz))
		{
		}
		~image2D() = default;
		irr::video::ITexture *image;
		vec2d<int> position;
		irr::core::rect<irr::s32> size;
	};
}


#endif //CPP_INDIE_STUDIO_IMAGE2D_HPP
