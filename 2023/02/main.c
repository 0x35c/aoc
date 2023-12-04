#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av) {
	int result = 0;
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

		int r = 0;
		int g = 0;
		int b = 0;
		for (int i = 0; input[i]; ++i) {
			int nb = atoi(&input[i]);
			for (;isdigit(input[i]); ++i);
			if (input[i] == 'r') {
				if (nb > r)
					r = nb;
			}
			else if (input[i] == 'g') {
				if (nb > g)
					g = nb;
			}
			else if (input[i] == 'b') {
				if (nb > b)
					b = nb;
			}
		}
		result += r * g * b;
		printf("%d\n", r * g * b);
	}
	free(input);
	fclose(stream);

	printf("%d\n", result);

	return (EXIT_SUCCESS);
}
