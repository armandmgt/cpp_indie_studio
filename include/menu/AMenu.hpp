/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** AMenu
*/

#ifndef AMENU_HPP
	#define AMENU_HPP
	#include "gfx/Renderer.hpp"
	#include "IScene.hpp"
	#include <string>

	namespace ids { namespace menu {
		class AMenu : public IScene {

			struct button {
				vec2d<int> pos;
				vec2d<int> size;
				irr::core::stringw inactive;
				irr::core::stringw active;
				SceneId	action;
				bool hovered;
			};
		public:
			explicit AMenu(gfx::Renderer *rend, SceneId id);
			AMenu() = default;
			~AMenu() = default;
			void computeEvent(vec2d<int> &mousePos);
			SceneId getSceneId();
		protected:
			bool setWindow();
			bool buttonEvent();
			gfx::Renderer *_rend;
			vec2d<int> _posBackground;
			irr::core::stringw _backgroundImg;
			std::vector<struct button> _infoButtons;
			SceneId		_id;
			vec2d<int>	_mousePos;

		};

	}}

#endif //AMENU_HPP
