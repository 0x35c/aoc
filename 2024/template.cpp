#include <iostream>
#include <string.h>
#include <string>
#include <vector>

int main(void)
{
	int result = 0;
	char *input = NULL;
	size_t size;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
	}
	free(input);

	printf("%d\n", result);

	return EXIT_SUCCESS;
}
