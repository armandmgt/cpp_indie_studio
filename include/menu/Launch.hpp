/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Launch
*/

#ifndef LAUNCH_HPP
#define LAUNCH_HPP

#include "menu/AMenu.hpp"

namespace ids { namespace menu {
	class Launch : public AMenu {
	public:
		struct items {
			std::string name;
			int timer;
			irr::core::stringw path;
			vec2d<int> pos;
		};

		explicit Launch(gfx::Renderer *rend);
		SceneId runPage() final;
		~Launch();
	private:
		void decorateScene();
		std::vector<struct items> _items;
	};
}}

#endif //LAUNCH_HPP
