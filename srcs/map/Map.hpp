/*
** EPITECH PROJECT, 2018
** Map
** File description:
**        Map generation
*/

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <map>

typedef enum direction {
	RIGHT,
	DOWN,
	LEFT,
	UP
}	direction;

typedef enum item {
	BREAKABLE_WALL = '*',
	BOMB = 'O',
	WALL_PASS = '|',
	SPEED_UP = 'S',
	BOMB_UP = 'B',
	FIRE_UP = 'F',
	EMPTY = ' '
}	item;

typedef struct pos_s {
	size_t x;
	size_t y;
} pos_t;

class Map
{
public:
	Map();
	Map(size_t, size_t);
	~Map();
	void initMap(size_t);
	std::vector<std::string> &getMap();
	void printMap() const;
	bool digPosition(size_t, size_t);
	void setCellItem(pos_t *, item);

private:
	std::vector<std::string> _map;
	size_t _length;
	size_t _width;
	bool addWall(size_t, size_t);
	void fillMap();
	void fillLine(std::string &);
	void proceduralGen(size_t);
	void digTopLeftCorner();
	void digTopRightCorner();
	void digBottomLeftCorner();
	void digBottomRightCorner();

	std::map<int, item> _gamble = {
		{40, BREAKABLE_WALL},
		{70, WALL_PASS},
		{80, SPEED_UP},
		{90, BOMB_UP},
		{100, FIRE_UP}
	};
};
