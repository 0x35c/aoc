#include <assert.h>
#include <stdlib.h>
#include <string>

int main(void)
{
	long result = 0;
	char *input = NULL;
	size_t size;
	int dial = 50;
	bool has_been_zeroed = false;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		int rotation = atoi(&input[1]);
		result += rotation / 100;
		rotation %= 100;
		if (input[0] == 'L') {
			if (dial == 0)
				has_been_zeroed = true;
			dial -= rotation;
			if (dial == 0)
				result++;
			else if (dial < 0) {
				if (has_been_zeroed)
					has_been_zeroed = false;
				else
					result++;
				dial += 100;
			}
		} else {
			dial += rotation;
			if (dial == 100)
				result++;
			else
				result += dial / 100;
			dial %= 100;
		}
	}
	free(input);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
