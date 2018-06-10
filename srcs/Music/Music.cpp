/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Music
*/

#include "common/Music.hpp"

bool ids::Music::musicInit()
{
	return _music.empty();
}

ids::Music::musicId ids::Music::createMusic(std::string &file)
{
	std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();

	music->openFromFile(file);
	music->setVolume(60);
	music->setLoop(true);

	_music.push_back({std::move(music), false});
	return _musicId++;
}

void ids::Music::playMusic(ids::Music::musicId music)
{
	if (music < _music.size()) {
		_music.at(music).sfMusic->play();
		_music.at(music).sfMusic->play();
		_music.at(music).active = true;
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
		_music.at(music).sfMusic->pause();
		_music.at(music).active = false;
	}
}