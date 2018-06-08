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
//#include <SFML/Audio/Export.hpp>
//#include <SFML/Audio/SoundStream.hpp>
//#include <SFML/Audio/Music.hpp>
//#include <SFML/Audio/InputSoundFile.hpp>
//#include <SFML/System/Mutex.hpp>
//#include <SFML/System/Time.hpp>
#include <memory>

namespace ids {
	class Music {
		using id = std::size_t;
//		struct Music {
//			sf::SoundBuffer buffer;
//			sf::Music mus;
//		};
	public:
		Music() noexcept;
		~Music() = default;
		bool	isPlaying();
		id createMusic(std::string &file);
		void playMusic(id music);
		void destroyMusic(id music);
		void pauseMusic(id music);
	private:
		std::unordered_map<id, std::unique_ptr<sf::Music>> _music{};
		id _musicId;
	};
}

#endif //CPP_INDIE_STUDIO_MUSIC_HPP
