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
		enum MusicId {
			ON, OFF, NONE
		};
		struct items {
			std::string name;
			MusicId state;
			irr::core::stringw soundOn;
			irr::core::stringw soundOff;
			vec2d<int> pos;
		};
		explicit Settings(gfx::Renderer *rend);
		~Settings() final;
	private:

		void settingsItems();
		void setMusicLevel();
		MusicId _music;
		std::vector<struct items> _items;

	};
}}

#endif //CPP_INDIE_STUDIO_SETTINGS_HPP
