/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Music
*/

#include <iostream>
#include "common/Music.hpp"

bool ids::Music::musicInit()
{
	return _music.empty();
}

bool ids::Music::getState(ids::Music::musicId music)
{
	return _music[music].active;
}

ids::Music::musicId ids::Music::createMusic(std::string &file)
{
	std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();

	music->openFromFile(file);
	music->setVolume(60);
	music->setLoop(true);

	_music.push_back({std::move(music), false});

	//_music.insert({_musicId, std::move(music)});
	return _musicId++;
}

void ids::Music::playMusic(ids::Music::musicId music)
{
	if (music < _music.size()) {
		_music[music].sfMusic->play();
		_music[music].active = true;
	}
}

void ids::Music::destroyMusic(ids::Music::musicId music)
{
	if (music < _music.size()) {
		_music.erase(_music.begin() + music);
	}
}

void ids::Music::pauseMusic(ids::Music::musicId music)
{
	if (music < _music.size()) {
		_music[music].sfMusic->pause();
		_music[music].active = false;
	}
}