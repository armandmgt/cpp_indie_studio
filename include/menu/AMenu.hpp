/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** AMenu
*/

#ifndef AMENU_HPP
#define AMENU_HPP

#include <string>
#include <memory>
#include "gfx/Renderer.hpp"
#include "scenes/IScene.hpp"
#include "music/Music.hpp"

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

			AMenu(std::shared_ptr<gfx::Renderer> rend, std::shared_ptr<Music> music, sceneId id);
			~AMenu() override = default;

		protected:
			bool setWindow();
			void buttonEvent();
			bool insideRect(vec2d<int> &pos, vec2d<int> &size);

			std::shared_ptr<gfx::Renderer> _rend;
			std::shared_ptr<Music> _musicManager;
			vec2d<int> _posBackground;
			sceneId	_id;
			evt::MyEventReceiver::MouseState _mouseData;
			irr::core::stringw _backgroundImg;
			std::vector<Button> _infoButtons;
		};
	}
}

#endif //AMENU_HPP
