#include <string>
#include <string.h>
#include <iostream>
#include <vector>

bool column_equal(const std::vector<std::string> &map, int col1, int col2) {
	for (auto i = 0; i < map.size(); ++i) {
		if (map[i][col1] != map[i][col2])
			return (false);
	}
	return (true);
}

bool fix_column(std::vector<std::string> &map, int col1, int col2) {
	int smudge = 0;
	int pos;
	for (auto i = 0; i < map.size(); ++i) {
		if (map[i][col1] != map[i][col2]) {
			++smudge;
			pos = i;
		}
	}
	if (smudge != 1)
		return (false);
	if (map[pos][col1] == '.')
		map[pos][col1] = '#';
	else
		map[pos][col1] = '.';
	return (true);
}

bool fix_row(std::vector<std::string> &map, int row1, int row2) {
	int smudge = 0;
	int pos;
	for (auto i = 0; i < map[0].size(); ++i) {
		if (map[row1][i] != map[row2][i]) {
			++smudge;
			pos = i;
		}
	}
	if (smudge != 1)
		return (false);
	if (map[row1][pos] == '.')
		map[row1][pos] = '#';
	else
		map[row1][pos] = '.';
	return (true);
}

int find_reflection(std::vector<std::string> &map, int first_reflection) {
	int result = 0;
	for (auto i = 0; i < map.size() - 1; ++i) {
		if (map[i] == map[i + 1]) {
			auto j = i - 1;
			auto k = i + 2;
			while (j >= 0 && k < map.size() && map[j] == map[k]) {
				--j;
				++k;
			}
			if (j < 0 || k == map.size()) {
				result = (i + 1) * 100;
				if (result == first_reflection)
					continue;
				// 	return (first_reflection);
				break;
			}
		}
	}
	if (result && result != first_reflection)
		return (result);
	for (auto i = 0; i < map[0].size() - 1; ++i) {
		if (column_equal(map, i, i + 1)) {
			auto j = i - 1;
			auto k = i + 2;
			while (j >= 0 && map[0][k] != '\n' && column_equal(map, j, k)) {
				--j;
				++k;
			}
			if (j < 0 || map[0][k] == '\n') {
				result = i + 1;
				if (result == first_reflection)
					continue;
				break;
				// if (result && result != first_reflection)
				// 	return (first_reflection);
			}
		}
	}
	if (result && result != first_reflection)
		return (result);
	return (0);
}

void restore_map(const std::vector<std::string> &map, std::vector<std::string> &map_cpy) {
	for (auto i = 0; i < map.size(); ++i) {
		for (auto k = 0; k < map[i].size(); ++k)
			map_cpy[i][k] = map[i][k];
	}
}

int main(void) {
	int result = 0;
	char *input = NULL;
	size_t size;

	std::vector<std::string> map;
	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (input[0] == '\n') {
			int first_reflection = find_reflection(map, 0);
			std::vector<std::string> map_cpy = map;
			for (auto i = 0; i < map_cpy.size(); ++i) {
				for (auto k = 0; map_cpy[i][k] != '\n'; ++k) {
					if (map_cpy[i][k] == '.')
						map_cpy[i][k] = '#';
					else
						map_cpy[i][k] = '.';
					auto res = find_reflection(map_cpy, first_reflection);
					if (res) {
						result += res;
						goto end;
					}
					restore_map(map, map_cpy);
				}
			}
end:
			map.clear();
			continue;
		}
		map.push_back(input);
	}
	free(input);

	printf("%d\n", result);

	return (EXIT_SUCCESS);
}
