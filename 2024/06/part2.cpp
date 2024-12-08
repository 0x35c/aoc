#include "../utils.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define CELL() map[y][x]

enum {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	START,
	IVENEVERPUTMYASSHERE,
	IVEPUTMYASSHERE,
	OBS
};

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

static int move_guard(std::vector<std::vector<int>> &map, int x, int y)
{
	int direction = UP;
	int count = 0;

	while (1) {
		count++;
		if (count >= 1000)
			return 1;
		switch (direction % 4) {
		case UP: {
			while (y >= 0 && CELL() != OBS) {
				CELL() = IVEPUTMYASSHERE;
				y--;
			}
			if (y < 0)
				return 0;
			y++;
			direction++;
		}
		case RIGHT: {
			while (x < map[y].size() && CELL() != OBS) {
				CELL() = IVEPUTMYASSHERE;
				x++;
			}
			if (x >= map[y].size())
				return 0;
			x--;
			direction++;
		}
		case DOWN: {
			while (y < map.size() && CELL() != OBS) {
				CELL() = IVEPUTMYASSHERE;
				y++;
			}
			if (y >= map.size())
				return 0;
			y--;
			direction++;
		}
		case LEFT: {
			while (x >= 0 && CELL() != OBS) {
				CELL() = IVEPUTMYASSHERE;
				x--;
			}
			if (x < 0)
				return 0;
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

	int startX;
	int startY;

	for (auto y = 0; y < map.size(); y++) {
		for (auto x = 0; x < map[y].size(); x++) {
			if (map[y][x] == START) {
				startX = x;
				startY = y;
			}
		}
	}

	for (auto y = 0; y < map.size(); y++) {
		for (auto x = 0; x < map[y].size(); x++) {
			if (map[y][x] == IVENEVERPUTMYASSHERE) {
				std::vector<std::vector<int>> clone = map;
				clone[y][x] = OBS;
				result += move_guard(clone, startX, startY);
			}
		}
	}

	printf("%d\n", result);

	return EXIT_SUCCESS;
}
