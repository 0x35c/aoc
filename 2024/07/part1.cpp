#include "../utils.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

enum { MUL, ADD, CAT };

static bool operate(const long res, const std::vector<long> &line, long value,
                    int op, int depth)
{
	if (op == ADD) {
		value += line[depth];
	} else if (op == MUL) {
		value *= line[depth];
	} else {
		char buf[64];
		sprintf(buf, "%ld%ld", value, line[depth]);
		value = atol(buf);
	}
	if (depth == line.size() - 1)
		return value == res;
	return operate(res, line, value, ADD, depth + 1) ||
	       operate(res, line, value, MUL, depth + 1) ||
	       operate(res, line, value, CAT, depth + 1);
}

int main(void)
{
	long result = 0;
	std::string input;

	while (std::getline(std::cin, input)) {
		std::vector<long> line = split_to_long(input, ' ');
		const long value = line[0];
		line.erase(line.begin());
		if (operate(value, line, 0, ADD, 0))
			result += value;
	}

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
