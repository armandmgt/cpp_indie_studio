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
#include "common/Music.hpp"

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

			struct Mouse {
				vec2d<int> pos;
				bool state;
			};

			explicit AMenu(gfx::Renderer *rend, sceneId id, ids::Music *music);
			~AMenu() override = default;
		protected:
			bool setWindow();
			void buttonEvent();
			bool insideRect(vec2d<int> &pos, vec2d<int> &size);
			gfx::Renderer *_rend;
			vec2d<int> _posBackground;
			irr::core::stringw _backgroundImg;
			std::vector<Button> _infoButtons;
			sceneId	_id;
			//Mouse _mouse;
			Music *_musicManager;
			evt::MyEventReceiver::MouseState _mouseData;
		};
	}
}

#endif //AMENU_HPP
