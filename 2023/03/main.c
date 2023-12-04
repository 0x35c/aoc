#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 140
#define HEIGHT 140

int extract_number(char *str, int j) {
	for (; j && isdigit(str[j]); --j);
	if (j == 0 && isdigit(str[j]))
		return (atoi(&str[j]));
	else
		return (atoi(&str[j + 1]));
}

int gear_ratio(char **strs, int i, int j) {
	int a = 0;
	int b = 0;
	int tmp;
	int valid = 0;
	// Check top line
	if (i > 0 && j > 0 && isdigit(strs[i - 1][j - 1])) {
		tmp = extract_number(strs[i - 1], j - 1);
		++valid;
		a = tmp;
	}
	if (i > 0 && isdigit(strs[i - 1][j])) {
		tmp = extract_number(strs[i - 1], j);
		if (!a) {
			++valid;
			a = tmp;
		}
		else if (!b && j > 0 && !isdigit(strs[i - 1][j - 1])) {
			++valid;
			b = tmp;
		}
	}
	if (i > 0 && j < WIDTH - 1 && isdigit(strs[i - 1][j + 1])) {
		tmp = extract_number(strs[i - 1], j + 1);
		if (!a) {
			++valid;
			a = tmp;
		}
		else if (!b && j > 0 && !isdigit(strs[i - 1][j])) {
			++valid;
			b = tmp;
		}
	}
	// Check middle line
	if (j > 0 && isdigit(strs[i][j - 1])) {
		tmp = extract_number(strs[i], j - 1);
		if (!a) {
			++valid;
			a = tmp;
		}
		else if (!b && tmp != a) {
			++valid;
			b = tmp;
		}
	}
	if (j < WIDTH - 1 && isdigit(strs[i][j + 1])) {
		tmp = extract_number(strs[i], j + 1);
		if (!a) {
			++valid;
			a = tmp;
		}
		else if (!b && tmp != a) {
			++valid;
			b = tmp;
		}
	}
	// Check bottom line
	if (i < HEIGHT - 1 && j > 0 && isdigit(strs[i + 1][j - 1])) {
		tmp = extract_number(strs[i + 1], j - 1);
		if (!a) {
			++valid;
			a = tmp;
		}
		else if (!b) {
			++valid;
			b = tmp;
		}
	}
	if (i < HEIGHT - 1 && isdigit(strs[i + 1][j])) {
		tmp = extract_number(strs[i + 1], j);
		if (!a) {
			++valid;
			a = tmp;
		}
		else if (!b && j > 0 && !isdigit(strs[i + 1][j - 1])) {
			++valid;
			b = tmp;
		}
	}
	if (i < HEIGHT - 1 &&  j < WIDTH - 1 && isdigit(strs[i + 1][j + 1])) {
		tmp = extract_number(strs[i + 1], j + 1);
		if (!a) {
			++valid;
			a = tmp;
		}
		else if (!b && !isdigit(strs[i + 1][j])) {
			++valid;
			b = tmp;
		}
	}
	if (valid == 2) {
		// printf("%d %d\n", a, b);
		return (a * b);
	}
	return (0);
}

int main(int ac, char **av) {
	char *strs[HEIGHT + 1];
	strs[HEIGHT] = NULL;
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
	int i = 0;
	while (1) {
		int rv = getline(&input, &size, stream);
		if (rv < 1)
			break;
		input[rv - 1] = '\0';
		strs[i] = strdup(input);
		++i;
	}
	free(input);
	fclose(stream);

	int count = 0;
	for (int i = 0; strs[i]; ++i) {
		for (int j = 0; j < WIDTH - 1; ++j) {
			if (strs[i][j] == '*') {
				result += gear_ratio(strs, i, j);
				++count;
			}
			/* This is part 1
			int nb = -1;
			int valid = 0;
			for (; j < WIDTH - 1 && !isdigit(strs[i][j]); ++j);
			pos = j;
			// Check left side
			if (isdigit(strs[i][j]) && i > 0 && j > 0 && strs[i - 1][j - 1] != '.')
					valid = 1;
			if (isdigit(strs[i][j]) && j > 0 && strs[i][j - 1] != '.')
				valid = 1;
			if (isdigit(strs[i][j]) && i < HEIGHT - 1 && j > 0 && strs[i + 1][j - 1] != '.')
					valid = 1;
			for (; j < WIDTH - 1 && isdigit(strs[i][j]); ++j) {
				// Check top row
				if (i > 0 && strs[i - 1][j] != '.')
						valid = 1;
				// Check bottom row
				if (i < HEIGHT - 1 && strs[i + 1][j] != '.')
						valid = 1;
			}
			// Check right side
			if (i > 0 && j != WIDTH - 1 && strs[i - 1][j] != '.')
					valid = 1;
			if (j != WIDTH - 1 && strs[i][j] != '.')
				valid = 1;
			if (i < HEIGHT - 1 && j != WIDTH - 1 && strs[i + 1][j] != '.')
					valid = 1;
			if (valid) {
				valid = 0;
				result += atoi(&strs[i][pos]);
			}
			*/
		}
	}
	for (int i = 0; strs[i]; ++i)
		free(strs[i]);

	printf("%d\n", result);

	return (EXIT_SUCCESS);
}
