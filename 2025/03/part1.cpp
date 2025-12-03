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
		auto ten = std::max_element(banks.begin(), banks.end() - 1);
		int unit = *std::max_element(ten + 1, banks.end());
		result += *ten * 10 + unit;
	}

	free(input);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
