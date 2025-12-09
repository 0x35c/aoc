#include "../utils.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

typedef struct {
	int64_t x;
	int64_t y;
} Point;

int main(void)
{
	int64_t result = 1;
	char *input = NULL;
	size_t size;
	std::vector<Point> boxes;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (input[rv - 1] == '\n') {
			input[rv - 1] = 0;
		}
		auto point = split_to_int(input, ',');
		boxes.push_back({point[0], point[1]});
	}
	free(input);

	for (auto i = 0; i < boxes.size() - 1; i++) {
		for (auto j = i + 1; j < boxes.size(); j++) {
			auto area = std::abs(boxes[i].x - boxes[j].x + 1) *
			            std::abs(boxes[i].y - boxes[j].y + 1);
			if (result < area)
				result = area;
		}
	}

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
