#include "../utils.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define CONNECTIONS_NB 1000

typedef struct point {
	int x;
	int y;
	int z;

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

static int uwufind(std::vector<int> &groups, int a)
{
	int root = a;
	while (root != groups[root])
		root = groups[root];

	while (a != root) {
		int next = groups[a];
		groups[a] = root;
		a = next;
	}

	return root;
}

static void uwunify(std::vector<int> &groups, std::vector<int> &sizes, int a,
                    int b)
{
	int root1 = uwufind(groups, a);
	int root2 = uwufind(groups, b);

	if (root1 == root2)
		return;
	sizes[root1] += sizes[root2];
	sizes[root2] = 0;
	groups[root2] = root1;
}

int main(void)
{
	long result = 1;
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
		boxes.push_back({point[0], point[1], point[2]});
	}
	free(input);

	auto distances = map_distances(boxes);
	std::sort(distances.begin(), distances.end());
	distances.erase(distances.begin() + CONNECTIONS_NB, distances.end());
	std::vector<int> groups(boxes.size());
	std::vector<int> sizes(boxes.size());
	for (auto i = 0; i < groups.size(); i++) {
		groups[i] = i;
		sizes[i] = 1;
	}
	for (auto i = 0; i < 10; i++) {
		for (auto e : distances) {
			int a = uwufind(
			    groups, std::find(boxes.begin(), boxes.end(), e.a) -
					boxes.begin());
			int b = uwufind(
			    groups, std::find(boxes.begin(), boxes.end(), e.b) -
					boxes.begin());
			uwunify(groups, sizes, a, b);
		}
	}
	std::sort(sizes.begin(), sizes.end(), std::greater<>());
	for (auto i = 0; i < 3; i++)
		result *= sizes[i];

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
