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

	for (long i = lstart; i <= lend; i++) {
		std::string s = std::to_string(i);
		int half = s.size() / 2;
		if (s.substr(0, half) == s.substr(half))
			invalids += i;
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
		range = split(input, '-');
		result += find_invalids(range[0], range[1]);
	}

	free(input);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
