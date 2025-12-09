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
static bool valid_point(const std::vector<Point> &points, const Point &p, int i)
{
	for (auto e : points) {
		switch (i) {
		case 0:
			if (e.x <= p.x && e.y <= p.y)
				return true;
			break;
		case 1:
			if (e.x >= p.x && e.y <= p.y)
				return true;
			break;
		case 2:
			if (e.x <= p.x && e.y >= p.y)
				return true;
			break;
		case 3:
			if (e.x >= p.x && e.y >= p.y)
				return true;
			break;
		}
	}
	return false;
}

static void sort_points(std::vector<Point> &rect)
{
	for (auto i = 0; i < 3; i++) {
		if (rect[i] == rect[i + 1])
			continue;
		if (rect[i].x >= rect[i + 1].x && rect[i].y >= rect[i + 1].y) {
			Point tmp = rect[i];
			rect[i] = rect[i + 1];
			rect[i + 1] = tmp;
			i = -1;
		}
	}
}

static bool valid_rectangle(const std::vector<Point> &points, Point a, Point b)
{
	std::vector<Point> rect = {a, b, {a.x, b.y}, {b.x, a.y}};
	sort_points(rect);

	int count = 0;

	// b is aligned with a on X axis and with d on Y axis
	// c is aligned with d on X axis and with a on Y axis
	// a....b
	// ......
	// ......
	// c....d
	// let's say we want to know if a point
	// is superior or equals to b/c
	//
	for (auto i = 0; i < 4; i++)
		if (valid_point(points, rect[i], i))
			count++;
	return count == 4;
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
