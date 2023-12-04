#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NB_LINE 199

int main(void) {
	int win[128];
	int tab[128];
	int amount[NB_LINE];
	memset(tab, -1, sizeof(tab));
	memset(win, -1, sizeof(win));
	for (int i = 0; i < NB_LINE; ++i) { amount[i] = 1; }
	int count = 0;
	int line = 0;
	int result = 0;
	char *input = NULL;
	size_t size;
	while (1) {
		count = 0;
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		int i;
		for (i = 0; input[i] != '|'; ++i) {
			if (isdigit(input[i])) {
				win[count] = atoi(&input[i]);
				++count;
			}
			for (;isdigit(input[i]); ++i);
		}
		count = 0;
		++i;
		for (; input[i]; ++i) {
			if (isdigit(input[i])) {
				tab[count] = atoi(&input[i]);
				++count;
			}
			for (;isdigit(input[i]); ++i);
		}
		count = 0;
		for (i = 0; tab[i] != -1; ++i) {
			for (int j = 0; win[j] != -1; ++j) {
				if (win[j] == tab[i])
					++count;
			}
		}
		for (int j = 0; j < amount[line]; ++j) {
			for (i = line + 1; i < line + count + 1; ++i) {
				amount[i]++;
			}
		}
		memset(tab, -1, sizeof(tab));
		memset(win, -1, sizeof(win));
		++line;
	}
	free(input);

	for (int i = 0; i < NB_LINE; ++i) {
		result += amount[i];
	}

	printf("%d\n", result);

	return (EXIT_SUCCESS);
}