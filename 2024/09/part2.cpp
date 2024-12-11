#include "../utils.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

int main(void)
{
	long result = 0;
	std::string input;
	std::vector<long> disk;

	while (std::getline(std::cin, input))
		for (auto i = 0; i < input.size(); i++)
			for (auto j = 0; j < input[i] - '0'; j++)
				disk.push_back((i % 2) ? -1 : (i / 2));

	long last = -1;
	for (auto i = disk.size() - 1; i > 0; i--) {
		if (disk[i] == -1)
			continue;
		int current = disk[i];
		int amount = i;
		while (i > 0 && current == disk[i])
			i--;
		amount -= i;
		i++;
		for (auto j = 0; j < disk.size() && j < i; j++) {
			const int pos = j;
			while (disk[j] == -1 && j < disk.size() &&
			       j - pos < amount)
				j++;
			if (j - pos == amount) {
				for (auto k = 0; k < amount; k++) {
					disk[k + pos] = current;
					disk[i + k] = -1;
				}
				last = j;
				if (i < last)
					goto end;
				break;
			}
		}
	}

end:
	for (auto i = 0; i < disk.size(); i++) {
		if (disk[i] == -1)
			continue;
		result += disk[i] * i;
	}

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
