#include "../utils.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

int main(void)
{
	long result = 0;
	char *input = NULL;
	size_t size;
	int count = 0;
	std::vector<std::string> map;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		count++;
		if (count % 2 == 0)
			continue;
		if (input[rv - 1] == '\n') {
			input[rv - 1] = 0;
		}
		map.push_back(input);
	}
	free(input);

	for (auto y = 0; y < map.size() - 1; y++) {
		for (auto x = 0; x < map[0].size(); x++) {
			if (map[y][x] == '.' || map[y][x] == '^')
				continue;
			if (map[y + 1][x] == '.') {
				map[y + 1][x] = '|';
				continue;
			} else if (map[y + 1][x] == '^') {
				result++;
				map[y + 1][x - 1] = '|';
				map[y + 1][x + 1] = '|';
			}
		}
	}

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
