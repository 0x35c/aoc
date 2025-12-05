#include "../utils.hpp"
#include <assert.h>
#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

typedef struct {
	long long min;
	long long max;
} Range;

static bool is_in_range(long long nb, Range range)
{
	return nb >= range.min && nb <= range.max;
}

static void remove_overlaps(std::vector<Range> &ranges)
{
	bool uwu;
	for (auto i = 0; i < ranges.size(); i++) {
		uwu = true;
		while (uwu) {
			uwu = false;
			for (auto j = 0; j < ranges.size(); j++) {
				if (j == i)
					continue;
				if (is_in_range(ranges[j].max, ranges[i]) &&
				    is_in_range(ranges[j].min, ranges[i])) {
					ranges.erase(ranges.begin() + j);
					continue;
				}
				if (is_in_range(ranges[j].min, ranges[i]) &&
				    ranges[j].max > ranges[i].max)
					ranges[i].max = ranges[j].max;
				else if (is_in_range(ranges[j].max,
				                     ranges[i]) &&
				         ranges[j].min < ranges[i].min)
					ranges[i].min = ranges[j].min;
				else
					continue;
				uwu = true;
				ranges.erase(ranges.begin() + j);
			}
		}
	}
}

int main(void)
{
	long long result = 0;
	char *input = NULL;
	size_t size;
	std::vector<Range> ranges;
	bool ingredients = false;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (input[rv - 1] == '\n')
			input[rv - 1] = 0;
		if (!*input)
			break;
		std::vector<long long> range = split_to_llong(input, '-');
		ranges.push_back({range[0], range[1]});
	}
	free(input);
	remove_overlaps(ranges);
	for (auto range : ranges)
		result += range.max - range.min + 1;

	printf("%lld\n", result);

	return EXIT_SUCCESS;
}
