/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Settings
*/

#ifndef CPP_INDIE_STUDIO_SETTINGS_HPP
#define CPP_INDIE_STUDIO_SETTINGS_HPP

#include "menu/AMenu.hpp"
#include "common/Music.hpp"

namespace ids { namespace menu {

	class Settings : public AMenu {
	public:
		enum musicState {
			ON, OFF, NONE
		};
		struct Items {
			vec2d<int> size;
			musicState state;
			irr::core::stringw soundOn;
			irr::core::stringw soundOff;
			vec2d<int> pos;
		};
		explicit Settings(gfx::Renderer *rend, ids::Music *music);
		~Settings() override;
		sceneId run() override;
	private:
		void	itemEvent();
		evt::MyEventReceiver &_events;
		musicState _music;
		std::vector<Items> _items;
	};
}}

#endif //CPP_INDIE_STUDIO_SETTINGS_HPP
