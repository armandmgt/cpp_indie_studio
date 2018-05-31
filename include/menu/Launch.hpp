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
		explicit Launch(gfx::Renderer *rend);
		~Launch() = default;

	private:
	};
}}

#endif //LAUNCH_HPP
