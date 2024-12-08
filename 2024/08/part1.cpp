#include "../utils.hpp"
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

	std::vector<std::string> clone = map;

	for (auto i = 0; i < antennas.size(); i++) {
		for (auto j = 0; j < antennas.size(); j++) {
			if (i == j || antennas[i].id != antennas[j].id)
				continue;
			const int dirX = antennas[j].x - antennas[i].x;
			const int dirY = antennas[j].y - antennas[i].y;
			if (inside_map(map, antennas[j].x + dirX,
			               antennas[j].y + dirY)) {
				clone[antennas[j].y + dirY]
				     [antennas[j].x + dirX] = '#';
			}
		}
	}

	for (auto line : clone) {
		std::cout << line << std::endl;
		for (auto c : line)
			if (c == '#')
				result++;
	}

	printf("%d\n", result);

	return EXIT_SUCCESS;
}
