/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Music
*/

#include <iostream>
#include "common/Music.hpp"

ids::Music::Music() noexcept : _musicId(0)
{
}

bool	ids::Music::isPlaying()
{
	return _music.size() > 0;
}

ids::Music::id ids::Music::createMusic(std::string &file)
{
	std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
	sf::SoundBuffer buffer;
	music->openFromFile(file);
	music->setVolume(60);
	music->setLoop(true);
	_music.insert({_musicId, std::move(music)});
	return _musicId++;
}

void ids::Music::playMusic(ids::Music::id music)
{
	auto it = _music.find(music);
	if (it != _music.end()) {
		it->second->play();
	}
}

void ids::Music::destroyMusic(ids::Music::id music)
{
	auto it = _music.find(music);
	_music.erase(it);
}

void ids::Music::pauseMusic(ids::Music::id music)
{
	auto it = _music.find(music);
	if (it != _music.end()) {
		it->second->pause();
	}
}