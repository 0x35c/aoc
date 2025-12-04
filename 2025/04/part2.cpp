#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

// yews forest
static bool roll_accessible(std::vector<std::string> map, int x, int y)
{
	int adjacent_rolls = 0;
	adjacent_rolls += x > 0 && map[y][x - 1] == '@';
	adjacent_rolls += x < map[0].size() - 1 && map[y][x + 1] == '@';
	adjacent_rolls += y > 0 && map[y - 1][x] == '@';
	adjacent_rolls += y < map.size() - 1 && map[y + 1][x] == '@';
	adjacent_rolls += x > 0 && y > 0 && map[y - 1][x - 1] == '@';
	adjacent_rolls += x < map[0].size() - 1 && y < map.size() - 1 &&
	                  map[y + 1][x + 1] == '@';
	adjacent_rolls +=
	    y > 0 && x < map[0].size() - 1 && map[y - 1][x + 1] == '@';
	adjacent_rolls +=
	    y < map.size() - 1 && x > 0 && map[y + 1][x - 1] == '@';
	return adjacent_rolls < 4;
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
	int replaced = 0;
	bool has_been_replaced = true;
	int prev_replaced;
	while (has_been_replaced) {
		has_been_replaced = false;
		for (auto y = 0; y < map.size(); y++) {
			for (auto x = 0; x < map[0].size(); x++) {
				if (map[y][x] == '@' &&
				    roll_accessible(map, x, y)) {
					map[y][x] = 'x';
					replaced++;
					has_been_replaced = true;
				}
			}
			result += replaced;
			prev_replaced = replaced;
			replaced = 0;
		}
	}

	free(input);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
