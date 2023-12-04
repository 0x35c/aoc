#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av) {
	int sum = 0;

	if (ac != 2) {
		dprintf(2, "Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}

	FILE *stream = fopen(av[1], "r");
	if (!stream) {
		perror("Could not open file");
		return (EXIT_FAILURE);
	}

	char *input = NULL;
	size_t size;
	while (1) {
		int rv = getline(&input, &size, stream);
		if (rv < 1)
			break;

		for (int i = 0; input[i]; ++i) {
			if (input[i] == '(')
				sum++;
			else if (input[i] == ')')
				sum--;
			if (sum == -1) {
				sum = i + 1;
				break ;
			}
		}
	}
	free(input);
	fclose(stream);

	printf("%d\n", sum);

	return (EXIT_SUCCESS);
}
