/*
** EPITECH PROJECT, 2018
** Map
** File description:
** Map generation
*/

#include "map/Map.hpp"

Map::Map() {}

Map::Map(size_t length, size_t width) : _length(length), _width(width) {}

void Map::setCellItem(map_pos *pos, map_item item)
{
	_map[pos->y][pos->x] = item;
}

bool Map::_addWall(size_t x, size_t y)
{
	auto rand = std::rand() % 100;

	if (_map[y][x] == BREAKABLE_WALL) {
		for (auto &it : _gamble)
			if (rand > it.first)
				continue;
			else {
				_map[y][x] = it.second;
				break;
			}
		return true;
	}
	return false;
}

bool Map::digPosition(size_t x, size_t y)
{
	if (_map[y][x] != UNBREAKABLE_WALL)
		_map[y][x] = EMPTY;
	return true;
}

void Map::_digBottomRightCorner()
{
	_map[_map.size() - 2][_map[1].size() - 2] = MAP_PLAYER;
	_map[_map.size() - 3][_map[1].size() - 2] = EMPTY;
	_map[_map.size() - 2][_map[1].size() - 3] = EMPTY;
}

void Map::_digBottomLeftCorner()
{
	_map[_map.size() - 2][1] = MAP_PLAYER;
	_map[_map.size() - 3][1] = EMPTY;
	_map[_map.size() - 2][2] = EMPTY;
}

void Map::_digTopRightCorner()
{
	_map[1][_map[1].size() - 2] = MAP_PLAYER;
	_map[1][_map[1].size() - 3] = EMPTY;
	_map[2][_map[1].size() - 2] = EMPTY;
}

void Map::_digTopLeftCorner()
{
	_map[1][1] = MAP_PLAYER;
	_map[2][1] = EMPTY;
	_map[1][2] = EMPTY;
}

void Map::_proceduralGen(size_t wallsToCreate)
{
	for (size_t i = 0; i < wallsToCreate - 1; i++) {
		size_t x = std::rand() % (_length);
		size_t y = std::rand() % (_width);
		_addWall(x, y);
	}
}

void Map::_fillLine(std::string &line)
{
	auto xMod = _length % 2 ? 3 : 2;

	for (size_t j = 1; j < _length; j++)
		if (j % xMod == 0)
			line[j] = UNBREAKABLE_WALL;
		else
			line[j] = BREAKABLE_WALL;
}

void Map::_fillMap()
{
	auto yMod = _width % 2 ? 3 : 2;

	_map.emplace_back(std::string(_length, UNBREAKABLE_WALL));
	for (size_t i = 1; i < _width; i++) {
		std::string tmp(_length, BREAKABLE_WALL);
		if (i % yMod == 0) {
			_fillLine(tmp);
		}
		tmp[0] = UNBREAKABLE_WALL;
		tmp[tmp.size() - 1] = UNBREAKABLE_WALL;
		_map.push_back(tmp);
	}
	_map.emplace_back(std::string(_length, UNBREAKABLE_WALL));
}

void Map::initMap(size_t wallPct)
{
	size_t totalCells = (_width - 1) * (_length - 1) / 2;
	size_t wallsToCreate = (totalCells * wallPct) / 100;

	_fillMap();
	_proceduralGen(wallsToCreate);
	_digTopLeftCorner();
	_digTopRightCorner();
	_digBottomLeftCorner();
	_digBottomRightCorner();
}

void Map::printMap() const
{
	for (auto const &it : _map) {
		std::cout << it << std::endl;
	}
}

