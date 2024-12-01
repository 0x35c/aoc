#include <bits/stdc++.h>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <vector>

std::vector<std::string> split(const char *s, char sep)
{
	std::vector<std::string> array;
	std::string e;

	for (auto i = 0; s[i] != '\n'; i++) {
		if (s[i] == sep) {
			if (!e.empty()) {
				array.push_back(e);
				e.clear();
			}
			continue;
		}
		e += s[i];
	}
	if (!e.empty())
		array.push_back(e);
	return array;
}

int main(void)
{
	long result = 0;
	char *input = NULL;
	size_t size;
	std::vector<int> left;
	std::vector<int> right;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		std::vector<std::string> line = split(input, ' ');
		left.push_back(atoi(line[0].c_str()));
		right.push_back(atoi(line[1].c_str()));
	}
	free(input);

	std::stable_sort(left.begin(), left.end());
	std::stable_sort(right.begin(), right.end());

	for (auto i = 0; i < right.size(); i++)
		result += std::abs(right[i] - left[i]);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
