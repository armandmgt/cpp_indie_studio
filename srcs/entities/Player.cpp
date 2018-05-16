/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Player
*/

#include "entities/Player.hpp"

ids::Player::Player(vec2d<float> pos, Color color, const std::string &name = "test")
	: _color(color), _name(name), _position(pos), _direction(DOWN), _speed(1) {}

vec2d<float> ids::Player::walk(const Directions direction) {
}

void ids::Player::putObject(IObject obj) {
}

void ids::Player::taunt() const {
}
