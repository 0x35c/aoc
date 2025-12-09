#include "../utils.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <string.h>
#include <string>
#include <vector>

int main(void)
{
	int64_t result = 0;
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

	std::map<int64_t, int64_t> beams;
	for (auto i = 1; i < map[0].size(); i++)
		beams.insert({i, 0});
	beams[map[0].size() / 2] = 1;
	for (auto line : map) {
		for (auto i = 0; i < line.size(); i++) {
			if (line[i] == '^') {
				beams[i - 1] += beams[i];
				beams[i + 1] += beams[i];
				beams[i] = 0;
			}
		}
	}
	for (auto e : beams)
		result += e.second;

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
