/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Music
*/

#ifndef CPP_INDIE_STUDIO_MUSIC_HPP
#define CPP_INDIE_STUDIO_MUSIC_HPP

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>

namespace ids {
	class Music {
		using musicId = std::size_t;
		struct Info {
			std::unique_ptr<sf::Music> sfMusic;
			bool active;
		};
	public:
		Music() = default;
		~Music() = default;
		bool	getState(musicId);
		musicId createMusic(std::string &file);
		void playMusic(musicId music);
		void destroyMusic(musicId music);
		void pauseMusic(musicId music);
		bool musicInit();
	private:

		//std::unordered_map<musicId, std::unique_ptr<sf::Music>> _music{};
		std::vector<Info> _music;
		musicId _musicId;
	};
}

#endif //CPP_INDIE_STUDIO_MUSIC_HPP
