#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <cstdbool>

typedef struct {
	int id;
	int x;
	int y;
	bool done;
} Node;

#define EXPANSION 1000000

// // This was my golem implementation for p1
// void fill_map(std::vector<std::vector<int>> &map) {
// 	// Add columns
// 	for (auto i = 0; i < map[0].size(); ++i) {
// 		auto k = 0;
// 		for (; k < map.size(); ++k) {
// 			if (map[k][i])
// 				break;
// 		}
// 		if (k == map.size()) {
// 			for (k = 0; k < map.size(); ++k) {
// 				map[k].insert(map[k].begin() + i, 0);
// 			}
// 			++i;
// 		}
// 	}
// 	// Add lines
// 	for (auto i = 0; i < map.size(); ++i) {
// 		auto k = 0;
// 		for (; k < map[i].size(); ++k) {
// 			if (map[i][k])
// 				break;
// 		}
// 		if (k == map[i].size()) {
// 			map.insert(map.begin() + i, std::vector<int>(map[0].size(), 0));
// 			++i;
// 		}
// 	}
// }

void parse_map(const std::vector<std::vector<int>> &map, std::vector<Node> &galaxies) {
	int empty_lines = 0;
	int empty_columns = 0;
	bool galaxyFound = false;
	for (auto i = 0; i < map.size(); ++i) {
		for (auto k = 0; k < map[i].size(); ++k) {
			if (map[i][k]) {
				Node galaxy = { map[i][k], 0, i + empty_lines, false };
				galaxies.push_back(galaxy);
				galaxyFound = true;
			}
		}
		if (!galaxyFound)
			empty_lines += EXPANSION - 1;
		galaxyFound = false;
	}
	for (auto i = 0; i < map[0].size(); ++i) {
		for (auto k = 0; k < map.size(); ++k) {
			if (map[k][i]) {
				galaxies[map[k][i] - 1].x = i + empty_columns;
				galaxyFound = true;
			}
		}
		if (!galaxyFound)
			empty_columns += EXPANSION - 1;
		galaxyFound = false;
	}
}

int main(void) {
	long result = 0;
	int galaxy = 1;
	int line = 0;
	char *input = NULL;
	size_t size;
	std::vector<std::vector<int>> map;
	std::vector<Node> galaxies;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		map.push_back({});
		for (auto i = 0; input[i]; ++i) {
			if (input[i] == '#')
				map[line].push_back(galaxy++);
			else
				map[line].push_back(0);
		}
		++line;
	}
	free(input);

	// fill_map(map); p1

	parse_map(map, galaxies);
	for (auto i = 0; i < galaxies.size(); ++i) {
		auto main = galaxies[i];
		for (auto k = 0; k < galaxies.size(); ++k) {
			if (galaxies[k].id == galaxies[i].id || galaxies[k].done)
				continue;
			auto subnode = galaxies[k];
			result += std::abs(subnode.x - main.x) + std::abs(subnode.y - main.y);
			// printf("result between %d and %d: %d\n", subnode.id, main.id, std::abs(subnode.x - main.x) + std::abs(subnode.y - main.y));
			// printf("coords of %d:\nx: %d y: %d\n", main.id, main.x, main.y);
			// printf("coords of %d:\nx: %d y: %d\n", subnode.id, subnode.x, subnode.y);
		}
		galaxies[i].done = true;
	}

	printf("%ld\n", result);

	return (EXIT_SUCCESS);
}
