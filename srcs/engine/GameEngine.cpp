/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Game Engine
*/

#include "engine/GameEngine.hpp"

ids::GameEngine::GameEngine() : _players(), _items(), _objects() {}

void ids::GameEngine::_spawnPlayer(std::pair<float, float>, ids::IPlayer::Color) {
}

void ids::GameEngine::_spawnItem(std::pair<float, float>, ids::IItem::Powerup) {
}

void ids::GameEngine::_spawnObject(std::pair<float, float>, ids::IObject::Type) {
}