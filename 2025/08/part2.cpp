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
	int64_t z;

	bool operator==(const struct point &other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}
	bool operator!=(const struct point &other) const
	{
		return x != other.x || y != other.y || z != other.z;
	}
} Point;

typedef struct distance {
	Point a;
	Point b;
	size_t norm;

	bool operator<(const struct distance &other) const
	{
		return norm < other.norm;
	}
} Distance;

static size_t calc_distance(Point a, Point b)
{
	auto uwu = pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2);
	return std::sqrt(uwu);
}

static std::vector<Distance> map_distances(std::vector<Point> &boxes)
{
	std::vector<Distance> distances;
	for (auto i = 0; i < boxes.size(); i++) {
		for (auto j = i + 1; j < boxes.size(); j++) {
			distances.push_back(
			    {boxes[i], boxes[j],
			     calc_distance(boxes[i], boxes[j])});
		}
	}
	return distances;
}

static int64_t uwufind(std::vector<int64_t> &groups, int64_t a)
{
	int64_t root = a;
	while (root != groups[root])
		root = groups[root];

	while (a != root) {
		int64_t next = groups[a];
		groups[a] = root;
		a = next;
	}

	return root;
}

static void uwunify(std::vector<int64_t> &groups, std::vector<int64_t> &sizes,
                    int64_t a, int64_t b)
{
	int64_t root1 = uwufind(groups, a);
	int64_t root2 = uwufind(groups, b);

	if (root1 == root2)
		return;
	sizes[root1] += sizes[root2];
	sizes[root2] = 0;
	groups[root2] = root1;
}

static bool survivor(std::vector<int64_t> sizes)
{
	int64_t count = 0;
	for (auto e : sizes)
		if (e)
			count++;
	return count == 1 ? true : false;
}

int main(void)
{
	int64_t result = 1;
	char *input = NULL;
	size_t size;
	std::vector<Point> boxes;

	while (1) {
		int64_t rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (input[rv - 1] == '\n') {
			input[rv - 1] = 0;
		}
		auto point = split_to_int(input, ',');
		boxes.push_back({point[0], point[1], point[2]});
	}
	free(input);

	auto distances = map_distances(boxes);
	std::sort(distances.begin(), distances.end());
	std::vector<int64_t> groups(boxes.size());
	std::vector<int64_t> sizes(boxes.size());
	for (auto i = 0; i < groups.size(); i++) {
		groups[i] = i;
		sizes[i] = 1;
	}
	while (1) {
		for (auto e : distances) {
			int64_t a = uwufind(
			    groups, std::find(boxes.begin(), boxes.end(), e.a) -
					boxes.begin());
			int64_t b = uwufind(
			    groups, std::find(boxes.begin(), boxes.end(), e.b) -
					boxes.begin());
			uwunify(groups, sizes, a, b);
			if (survivor(sizes)) {
				result = e.a.x * e.b.x;
				goto exit_loop;
			}
		}
	}
exit_loop:

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
