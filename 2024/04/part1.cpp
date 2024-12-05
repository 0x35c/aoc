#include <iostream>
#include <string>
#include <vector>

typedef struct {
	int x;
	int y;
} s_dir;

static char get_cell(const std::vector<std::string> &map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map[0].size() || y >= map.size())
		return -1;
	return map[y][x];
}

static bool check_cell(const std::vector<std::string> &map, int x, int y,
                       char c, s_dir dir)
{
	if (get_cell(map, x + dir.x, y + dir.y) == c)
		return (c != 'S')
		           ? check_cell(map, x + dir.x, y + dir.y, 'S', dir)
		           : true;
	return false;
}

int main(void)
{
	int result = 0;
	std::string input;
	std::vector<std::string> map;

	while (std::getline(std::cin, input))
		map.push_back(input);

	for (auto y = 0; y < map.size(); y++) {
		for (auto x = 0; x < map[y].size(); x++) {
			if (map[y][x] != 'X')
				continue;
			if (get_cell(map, x - 1, y) == 'M')
				result +=
				    check_cell(map, x - 1, y, 'A', {-1, 0});
			if (get_cell(map, x - 1, y - 1) == 'M')
				result += check_cell(map, x - 1, y - 1, 'A',
				                     {-1, -1});
			if (get_cell(map, x, y - 1) == 'M')
				result +=
				    check_cell(map, x, y - 1, 'A', {0, -1});
			if (get_cell(map, x + 1, y - 1) == 'M')
				result +=
				    check_cell(map, x + 1, y - 1, 'A', {1, -1});
			if (get_cell(map, x + 1, y) == 'M')
				result +=
				    check_cell(map, x + 1, y, 'A', {1, 0});
			if (get_cell(map, x + 1, y + 1) == 'M')
				result +=
				    check_cell(map, x + 1, y + 1, 'A', {1, 1});
			if (get_cell(map, x, y + 1) == 'M')
				result +=
				    check_cell(map, x, y + 1, 'A', {0, 1});
			if (get_cell(map, x - 1, y + 1) == 'M')
				result +=
				    check_cell(map, x - 1, y + 1, 'A', {-1, 1});
		}
	}

	printf("%d\n", result);

	return EXIT_SUCCESS;
}
