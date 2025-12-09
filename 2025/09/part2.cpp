#include "../utils.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

typedef struct point {
	int64_t x;
	int64_t y;

	bool operator==(const struct point &other) const
	{
		return x == other.x && y == other.y;
	}
} Point;

/*
..............
.......#XXX#..
.......XXXXX..
..#XXXX#XXXX..
..XXXXXXXXXX..
..#XXXXXX#XX..
.........XXX..
.........#X#..
..............
*/

/*
7,1
11,1
11,7
9,7
9,5
2,5
2,3
7,3
 */

static bool valid_rectangle(const std::vector<Point> &points, const Point &a,
                            const Point &b)
{
	// int normX = std::abs(b.x - a.x);
	// int normY = std::abs(b.y - a.y);
	Point cornerA = {a.x, b.y};
	Point cornerB = {b.x, a.y};
	int count = 0;

	for (auto e : points) {
	}
	return false;
}

int main(void)
{
	int64_t result = 1;
	char *input = NULL;
	size_t size;
	std::vector<Point> points;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (input[rv - 1] == '\n') {
			input[rv - 1] = 0;
		}
		auto point = split_to_int(input, ',');
		points.push_back({point[0], point[1]});
	}
	free(input);

	for (auto i = 0; i < points.size() - 1; i++) {
		for (auto j = i + 1; j < points.size(); j++) {
			if (valid_rectangle(points, points[i], points[j])) {
				auto area =
				    std::abs(points[i].x - points[j].x + 1) *
				    std::abs(points[i].y - points[j].y + 1);
				if (result < area)
					result = area;
			}
		}
	}

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
