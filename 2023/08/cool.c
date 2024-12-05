#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define auto __auto_type
#define MAP_SIZE 718
#define RIGHT 0
#define LEFT 1
#define size 6

typedef struct {
	char ref[4];
	char right[4];
	char left[4];
} Element;

typedef struct {
	void *p[2];
	char notZ;
} Element_opti;

static const char instructions[] = { 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0,
0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0,
1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1,
1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1,
1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0,
1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0,
0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0,
1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1,
0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0,
0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0,
1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1 };

static Element map[MAP_SIZE + 1];
static Element_opti map_opti[MAP_SIZE + 1];
static Element_opti *elements[size];

static Element_opti *find_element(const char *ref) {
	for (auto i = 0; i < MAP_SIZE; ++i) {
		if (!strcmp(ref, map[i].ref))
			return (&map_opti[i]);
	}
}

static void link_elements(void) {
	for (auto i = 0; i < MAP_SIZE; ++i) {
		map_opti[i].p[LEFT] = find_element(map[i].left);
		map_opti[i].p[RIGHT] = find_element(map[i].right);
	}
}

static int find_first_elements(void) {
	int count = 0;
	for (auto i = 0; i < MAP_SIZE; ++i) {
		if ('A' == map[i].ref[2]) {
			elements[count] = &map_opti[i];
			++count;
		}
	}
	return (count);
}

static bool check_valid(void) {
	for (auto index = 0; index < size; ++index) {
		if (elements[index]->notZ)
			return (false);
	}
	return (true);
}

int main(void) {
	long result = 0;
	int line = 0;
	char *input = NULL;
	size_t size_fdp;
	while (1) {
		int i = 0;
		int rv = getline(&input, &size_fdp, stdin);
		if (rv < 1)
			break;
		for (auto count = 0; count < 3; ++count) {
			while (input[i] != ' ' && input[i] != '\n')
				++i;
			input[i] = '\0';
			if (count == 0) {
				strcpy(map[line].ref, &input[i - 3]);
				if (map[line].ref[2] != 'Z')
					map_opti[line].notZ = true;
			}
			if (count == 1)
				strcpy(map[line].left, &input[i - 3]);
			if (count == 2)
				strcpy(map[line].right, &input[i - 3]);
			++i;
		}
		++line;
	}
	free(input);

	link_elements();
	find_first_elements();
	// printf("%ld\n", size);
	while (1) {
		for (auto i = 0; i < sizeof(instructions); ++i) {
			for (auto index = 0; index < size; ++index) {
				// Omega cringe low
				// if (instructions[i] == 'R')
				// 	elements[index] = elements[index]->p_right;
				// else
				// 	elements[index] = elements[index]->p_left;
				// Cringe low
				// elements[index] = (void *)(((instructions[i] == 1) *
				// (uintptr_t)elements[index]->p_right) |
				// ((uintptr_t)elements[index]->p_left * (instructions[i] != 1)));
				elements[index] = (instructions[i]) ?
				elements[index]->p[RIGHT] : elements[index]->p[LEFT];
				// elements[index] = elements[index]->p[instructions[i] != 0];
			}
		}
		result += size * sizeof(instructions);
		if (result % 307000000 == 0) {
			double percent = (result * 100) / 12000000000000.;
			printf("%lf\n", percent);
		}
		if (check_valid()) {
			printf("%ld\n", result);
			return (EXIT_SUCCESS);
		}
	}

	return (EXIT_SUCCESS);
}
