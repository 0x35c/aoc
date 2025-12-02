#include "../utils.hpp"
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

static long find_invalids(std::string start, std::string end)
{
	long lstart = atol(start.c_str());
	long lend = atol(end.c_str());
	long invalids = 0;
	std::string pattern;
	int uwu = 0;

	for (long value = lstart; value <= lend; value++) {
		std::string s = std::to_string(value);
		pattern = s[0]; // this is needed for the modulo at the start :D
		for (auto i = 0; i < s.size(); i++) {
			uwu = 0;
			while (uwu < s.size() &&
			       s[uwu] == pattern[uwu % pattern.size()])
				uwu++;
			if (uwu == s.size() && uwu % pattern.size() == 0) {
				if (s.size() > 1)
					invalids += value;
				break;
			}
			if (i)
				pattern += s[i];
		}
	}

	return invalids;
}

int main(void)
{
	long result = 0;
	char *input = NULL;
	size_t size;
	std::vector<std::string> range;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (input[rv - 1] == '\n')
			input[rv - 1] = '\0';
		range = split(input, '-');
		result += find_invalids(range[0], range[1]);
	}

	free(input);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
