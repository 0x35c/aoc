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

	for (auto i = 0; i < left.size(); i++) {
		int count = 0;
		for (auto j = 0; j < right.size(); j++)
			if (right[j] == left[i])
				count++;
		result += count * left[i];
	}

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
