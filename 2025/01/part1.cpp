#include <assert.h>
#include <stdlib.h>
#include <string>

int main(void)
{
	long result = 0;
	char *input = NULL;
	size_t size;
	int dial = 50;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		int rotation = atoi(&input[1]) % 100;
		if (input[0] == 'L')
			dial -= rotation;
		else
			dial += rotation;
		dial %= 100;
		if (dial == 0)
			result++;
	}
	free(input);

	printf("%ld\n", result);

	return EXIT_SUCCESS;
}
