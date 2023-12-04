#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av) {
	int x = -1;
	int y = -1;
	int sum = 0;

	if (ac < 2) {
		dprintf(2, "Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}

	for (int i = 1; av[i]; ++i) {
		for (int j = 0; av[i][j]; ++j) {
			if (isdigit(av[i][j])) {
				if (x == -1)
					x = av[i][j] - '0';
				else
					y = av[i][j] - '0';
			}
		}
		if (y == -1)
			y = x;
		sum += x * 10 + y;
		x = -1;
		y = -1;
	}
	printf("%d\n", sum);

	return (EXIT_SUCCESS);
}
