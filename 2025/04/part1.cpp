#include "../utils.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

static bool roll_accessible(std::vector<std::string> map, int x, int y)
{
	int adjacent_rolls = 0;
	if (x > 0 && map[y][x - 1] == '@')
		adjacent_rolls++;
	if (x < map[0].size() - 1 && map[y][x + 1] == '@')
		adjacent_rolls++;
	if (y > 0 && map[y - 1][x] == '@')
		adjacent_rolls++;
	if (y < map.size() - 1 && map[y + 1][x] == '@')
		adjacent_rolls++;

	if (x > 0 && y > 0 && map[y - 1][x - 1] == '@')
		adjacent_rolls++;
	if (x < map[0].size() - 1 && y < map.size() - 1 &&
	    map[y + 1][x + 1] == '@')
		adjacent_rolls++;
	if (y > 0 && x < map[0].size() - 1 && map[y - 1][x + 1] == '@')
		adjacent_rolls++;
	if (y < map.size() - 1 && x > 0 && map[y + 1][x - 1] == '@')
		adjacent_rolls++;
	if (adjacent_rolls < 4)
		return true;
	return false;
}

int main(void)
{
	long result = 0;
	char *input = NULL;
	size_t size;
	std::vector<std::string> map;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (input[rv - 1] == '\n')
			input[rv - 1] = 0;
		map.push_back(input);
	}
	for (auto y = 0; y < map.size(); y++) {
		for (auto x = 0; x < map[0].size(); x++) {
			if (map[y][x] == '@')
				result += roll_accessible(map, x, y);
		}
	}

	free(input);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
