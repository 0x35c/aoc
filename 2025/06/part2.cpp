#include <bits/stdc++.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#define NB_LINES 4

static uint64_t calculate_problem(const std::vector<std::string> &grid,
                                  int last_column, std::string values[4])
{
	char operand = grid[grid.size() - 1][last_column];
	uint64_t solution = operand == '*' ? 1 : 0;
	for (auto i = 0; i < NB_LINES; i++) {
		if (values[i].empty())
			continue;
		int nb = atoi(values[i].c_str());
		if (operand == '*')
			solution *= nb;
		else
			solution += nb;
		values[i].erase();
	}
	return solution;
}

int main(void)
{
	uint64_t result = 0;
	char *input = NULL;
	size_t size;
	std::vector<std::string> grid;

	// Parsing
	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (input[rv - 1] == '\n') {
			input[rv - 1] = 0;
		}
		grid.push_back(input);
	}
	free(input);

	// Problem solving
	int last_column = 0;
	std::string values[NB_LINES]{};
	for (auto x = 0; x < grid[0].size(); x++) {
		if (grid[0][x] == ' ') {
			int spaces = 0;
			for (auto y = 0; y < grid.size() - 1; y++)
				if (grid[y][x] == ' ')
					spaces++;
			if (spaces < grid.size() - 1)
				goto fill_values;
			result += calculate_problem(grid, last_column, values);
			x++;
			if (x >= grid[0].size())
				break;
			last_column = x;
		}
	fill_values:
		for (auto y = 0; y < grid.size() - 1; y++)
			if (grid[y][x] != ' ')
				values[x - last_column] += grid[y][x];
		// ok this if is probably bc of some condition
		// i fucked up elsewhere but it works
		if (x + 1 == grid[0].size())
			result += calculate_problem(grid, last_column, values);
	}

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
