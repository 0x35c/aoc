#include <assert.h>
#include <stdlib.h>
#include <string>

int main(void)
{
	long result = 0;
	char *input = NULL;
	size_t size;
	int dial = 50;

	int line = 0;
	while (1) {
		int rv = getline(&input, &size, stdin);
		line++;
		if (rv < 1)
			break;
		int rotation = atoi(&input[1]) % 100;
		if (input[0] == 'L') {
			dial -= rotation;
			if (dial == 0)
				result++;
			else if (dial < 0)
				dial += 100;
		} else {
			dial += rotation;
			if (dial == 100)
				result++;
			dial %= 100;
		}
	}
	free(input);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
