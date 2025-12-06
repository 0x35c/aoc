#include "../utils.hpp"
#include <bits/stdc++.h>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <string>
#include <vector>

int main(void)
{
	long result = 0;
	char *input = NULL;
	size_t size;
	std::vector<std::stack<std::string>> problems;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (input[rv - 1] == '\n') {
			input[rv - 1] = 0;
		}
		std::vector<std::string> values = split(input, ' ');
		if (problems.size() == 0)
			problems.resize(values.size());
		for (auto i = 0; i < values.size(); i++)
			problems[i].push(values[i].c_str());
	}
	free(input);
	for (auto e : problems) {
		std::string operand = e.top();
		e.pop();
		long solution = operand == "*" ? 1 : 0;
		while (!e.empty()) {
			int value = atoi(e.top().c_str());
			e.pop();
			if (operand == "*")
				solution *= value;
			else
				solution += value;
		}
		result += solution;
	}

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
