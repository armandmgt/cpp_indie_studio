/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Settings
*/

#ifndef CPP_INDIE_STUDIO_SETTINGS_HPP
#define CPP_INDIE_STUDIO_SETTINGS_HPP

#include "menu/AMenu.hpp"

namespace ids { namespace menu {

	class Settings : public AMenu {
	public:
		enum musicState {
			ON, OFF, NONE
		};
		struct Items {
			std::string name;
			musicState state;
			irr::core::stringw soundOn;
			irr::core::stringw soundOff;
			vec2d<int> pos;
		};
		explicit Settings(gfx::Renderer *rend);
		~Settings() override;
		sceneId run() override;
	private:

		void settingsItems();
		void setMusicLevel();
		musicState _music;
		std::vector<Items> _items;
	};
}}

#endif //CPP_INDIE_STUDIO_SETTINGS_HPP
