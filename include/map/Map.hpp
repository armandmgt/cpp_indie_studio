/*
** EPITECH PROJECT, 2018
** Map
** File description:
**        Map generation
*/

#include <vector>
#include <string>
#include <iostream>
#include <map>

enum direction {
	RIGHT,
	DOWN,
	LEFT,
	UP
};

enum map_item {
	BREAKABLE_WALL = '*',
	BOMB = 'O',
	KICK_POWERUP = '|',
	SPEED_UP = 'S',
	BOMB_UP = 'B',
	FIRE_UP = 'F',
	EMPTY = ' '
};

struct map_pos {
	size_t x;
	size_t y;
};

class Map
{
public:
	Map();
	Map(size_t l, size_t w);
	~Map() noexcept = default;

	void initMap(size_t);
	std::vector<std::string> &getMap() { return this->_map; };
	void printMap() const;
	bool digPosition(size_t, size_t);
	void setCellItem(map_pos *, map_item);

private:
	std::vector<std::string> _map;
	size_t _length;
	size_t _width;
	bool _addWall(size_t, size_t);
	void _fillMap();
	void _fillLine(std::string &);
	void _proceduralGen(size_t);
	void _digTopLeftCorner();
	void _digTopRightCorner();
	void _digBottomLeftCorner();
	void _digBottomRightCorner();

	std::map<int, map_item> _gamble = {
		{40, BREAKABLE_WALL},
		{70, KICK_POWERUP},
		{80, SPEED_UP},
		{90, BOMB_UP},
		{100, FIRE_UP}
	};
};
