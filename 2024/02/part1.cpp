#include <bits/stdc++.h>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <vector>

static std::vector<std::string> split(const char *s, char sep)
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

static bool issafe(std::vector<std::string> line)
{
	int direction = 0;
	for (auto i = 0; i < line.size() - 1; i++) {
		int a = atoi(line[i].c_str());
		int b = atoi(line[i + 1].c_str());
		int distance = std::abs(a - b);
		if (!direction)
			direction = b < a ? 1 : -1;
		if (direction == 1 && a < b)
			return false;
		else if (direction == -1 && a > b)
			return false;
		if (distance < 1 || distance > 3)
			return false;
	}
	return true;
}

int main(void)
{
	long result = 0;
	char *input = NULL;
	size_t size;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		std::vector<std::string> line = split(input, ' ');
		result += issafe(line);
	}
	free(input);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
