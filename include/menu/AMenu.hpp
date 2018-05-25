/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** AMenu
*/

#ifndef AMENU_HPP
	#define AMENU_HPP
	#include "gfx/Renderer.hpp"

	namespace ids { namespace menu {
		class AMenu {
			enum SceneId {
				GAME, QUIT, MENU, SETTINGS, SCORE, PAUSE
			};
		public:
			AMenu(shared_ptr<Renderer> rend);
			virtual ~AMenu();
		protected:
			bool setWindow();
			void computeEvent();
			State getSceneId();
			Renderer &_rend;
			std::vector<vec2d<int>> _posBackground;
		};
	}}

#endif //AMENU_HPP
