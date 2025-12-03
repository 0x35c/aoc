#include "../utils.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

int main(void)
{
	long result = 0;
	char *input = NULL;
	size_t size;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (input[rv - 1] == '\n')
			input[rv - 1] = 0;
		std::vector<int> banks;
		for (auto i = 0; input[i]; i++)
			banks.push_back(input[i] - '0');

		auto prev = banks.begin();
		for (auto i = 11; i >= 0; i--) {
			auto e = std::max_element(prev, banks.end() - i);
			result += *e * std::pow(10, i);
			prev = e + 1;
		}
	}

	free(input);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
