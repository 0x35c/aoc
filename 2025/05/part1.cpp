#include "../utils.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

typedef struct {
	long min;
	long max;
} Range;

static bool is_in_range(long nb, std::vector<Range> ranges)
{
	for (auto range : ranges)
		if (nb <= range.max && nb >= range.min)
			return true;
	return false;
}

int main(void)
{
	long result = 0;
	char *input = NULL;
	size_t size;
	std::vector<Range> ranges;
	bool ingredients = false;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (input[rv - 1] == '\n') {
			input[rv - 1] = 0;
		}
		if (!*input) {
			ingredients = true;
			continue;
		}
		if (ingredients) {
			result += is_in_range(atol(input), ranges);
		} else {
			std::vector<long> range = split_to_long(input, '-');
			ranges.push_back({range[0], range[1]});
		}
	}
	free(input);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
