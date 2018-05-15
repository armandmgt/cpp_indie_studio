/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Renderable
*/

#ifndef CPP_INDIE_STUDIO_RENDERABLE_HPP
#define CPP_INDIE_STUDIO_RENDERABLE_HPP

#include <string>
#include <unordered_map>
#include "common/vec.hpp"
#include "enum/AnimationType.hpp"

namespace gfx {

	class Renderable {
	public:
		Renderable() = default;
		~Renderable() = default;
		void pushOnScreen();
		void removeFromScreen();
		void setAnimation(AnimationType, const std::string &);
		void setMesh(std::string const &);
		void setTexture(const std::string &);
		vec3d<float> getPosition() const;
		void render();
		void setPosition(vec3d<float> const &);
		void playAnimation(AnimationType) const;
		bool is3D() const;
		bool isAnimable() const;

//	private:
		// std::unordered_map<AnimationType, Animation> animationMap;

	};
};


#endif //CPP_INDIE_STUDIO_RENDERABLE_HPP
