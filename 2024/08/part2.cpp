#include "../utils.hpp"
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

typedef struct {
	int x;
	int y;
	char id;
} s_antenna;

static bool inside_map(const std::vector<std::string> &map, int x, int y)
{
	if (x < 0 || x >= map[0].size() || y < 0 || y >= map.size())
		return false;
	return true;
}

int main(void)
{
	int result = 0;
	std::string input;
	std::vector<std::string> map;
	std::vector<s_antenna> antennas;

	while (std::getline(std::cin, input))
		map.push_back(input);

	for (auto y = 0; y < map.size(); y++)
		for (auto x = 0; x < map[0].size(); x++)
			if (map[y][x] != '.')
				antennas.push_back({x, y, map[y][x]});

	for (auto i = 0; i < antennas.size(); i++) {
		for (auto j = 0; j < antennas.size(); j++) {
			if (i == j || antennas[i].id != antennas[j].id)
				continue;
			const int dirX = antennas[j].x - antennas[i].x;
			const int dirY = antennas[j].y - antennas[i].y;
			int x = antennas[j].x;
			int y = antennas[j].y;
			while (inside_map(map, x, y)) {
				map[y][x] = '#';
				x += dirX;
				y += dirY;
			}
		}
	}

	for (auto line : map)
		result += std::count(line.begin(), line.end(), '#');

	printf("%d\n", result);

	return EXIT_SUCCESS;
}
