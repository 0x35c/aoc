#include "../utils.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define CELL() map[y][x]

#define START                -1
#define IVENEVERPUTMYASSHERE 0
#define OBS                  1
#define IVEPUTMYASSHERE      2

enum { UP = 0, RIGHT, DOWN, LEFT };

static void fill_map(std::vector<std::vector<int>> &map, std::string input)
{
	std::vector<int> translated;
	for (auto c : input) {
		if (c == '.')
			translated.push_back(IVENEVERPUTMYASSHERE);
		else if (c == '#')
			translated.push_back(OBS);
		else if (c == '^')
			translated.push_back(START);
	}
	map.push_back(translated);
}

static void move_guard(std::vector<std::vector<int>> &map, int x, int y)
{
	int direction = UP;
	while (1) {
		switch (direction % 4) {
		case UP: {
			while (y >= 0 && CELL() != OBS) {
				CELL() = IVEPUTMYASSHERE;
				y--;
			}
			if (y < 0)
				return;
			y++;
			direction++;
		}
		case RIGHT: {
			while (x < map[y].size() && CELL() != OBS) {
				CELL() = IVEPUTMYASSHERE;
				x++;
			}
			if (x >= map[y].size())
				return;
			x--;
			direction++;
		}
		case DOWN: {
			while (y < map.size() && CELL() != OBS) {
				CELL() = IVEPUTMYASSHERE;
				y++;
			}
			if (y >= map.size())
				return;
			y--;
			direction++;
		}
		case LEFT: {
			while (x >= 0 && CELL() != OBS) {
				CELL() = IVEPUTMYASSHERE;
				x--;
			}
			if (x < 0)
				return;
			x++;
			direction++;
		}
		}
	}
}

int main(void)
{
	int result = 0;
	std::string input;
	std::vector<std::vector<int>> map;

	while (std::getline(std::cin, input)) {
		if (input.empty())
			break;
		fill_map(map, input);
	}

	for (auto y = 0; y < map.size(); y++)
		for (auto x = 0; x < map[y].size(); x++)
			if (map[y][x] == START)
				move_guard(map, x, y);

	for (auto line : map)
		for (auto c : line)
			result += (c == IVEPUTMYASSHERE) ? 1 : 0;

	printf("%d\n", result);

	return EXIT_SUCCESS;
}
