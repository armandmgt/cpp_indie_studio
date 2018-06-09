/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** image2D
*/
#ifndef CPP_INDIE_STUDIO_IMAGE2D_HPP
#define CPP_INDIE_STUDIO_IMAGE2D_HPP

#include <irrlicht/ITexture.h>
#include <utility>
#include "common/vec.hpp"

namespace gfx {
	class Image2D {
	public:
		Image2D() = default;
		Image2D(const irr::core::stringw &f, irr::video::ITexture *t, const vec2d<int> &p,
			irr::core::rect<irr::s32> s)
			: filename(f), texture(t), position(p), size(std::move(s))
		{}
		Image2D(Image2D &&other) noexcept : filename(other.filename), texture(other.texture),
			position(other.position), size(std::move(other.size))
		{}
		Image2D &operator=(Image2D &&other) noexcept {
			filename = other.filename;
			texture = other.texture;
			position = other.position;
			size = std::move(other.size);
			return *this;
		}
		~Image2D() {
			texture->drop();
		}

		irr::core::stringw filename;
		irr::video::ITexture *texture{};
		vec2d<int> position{};
		irr::core::rect<irr::s32> size;
	};
}


#endif //CPP_INDIE_STUDIO_IMAGE2D_HPP
