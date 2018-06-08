/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** AMenu
*/

#ifndef AMENU_HPP
#define AMENU_HPP

#include <string>
#include "gfx/Renderer.hpp"
#include "scenes/IScene.hpp"

namespace ids {
	namespace menu {

		class AMenu : public IScene {
		public:
			struct Button {
				vec2d<int> pos;
				vec2d<int> size;
				irr::core::stringw inactive;
				irr::core::stringw active;
				sceneId	action;
				bool hovered;
			};

			explicit AMenu(gfx::Renderer *rend, sceneId id);
			~AMenu() override = default;

			void computeEvent(evt::MyEventReceiver::MouseState &mouseData);

		protected:
			bool setWindow();
			void buttonEvent();
			gfx::Renderer *_rend;
			vec2d<int> _posBackground;
			irr::core::stringw _backgroundImg;
			std::vector<Button> _infoButtons;
			sceneId	_id;
			std::pair<vec2d<int>, bool> _mousePos;

		};
	}
}

#endif //AMENU_HPP
