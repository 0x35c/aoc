#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define auto __auto_type
#define MAP_SIZE 718
#define size 6

typedef struct {
	char ref[4];
	char right[4];
	char left[4];
} Element;

const char instructions[] = "LRRLLRLLRRLRRLLRRLLRLRRRLLRRLRRRLRRLRRRLLRRLLRLLRRLRLRRRLRRLLRRRLRLRRLRRLRLRLRLLRLRRRLLRLLRRLRRRLRLRLRRRLRRLLRRRLRLRRLRRLLRRLRRRLRRLRRLRRLLRLRLRRLLRLLRRRLRRLRRLRRRLRLLRRRLRRRLRRLLRRRLRRRLRLLRLRRLRLLRRLLLRRLRRLRRLRLRRRLRRLLRLRRRLRRLRLLLRRLRRLRRRLLLRLLLLRRLRLLLRLRRRLRRRLRLRRRLLLLRLRRRLRLLLRRLRLRRLRRLRRRLRRRR";
Element map[MAP_SIZE + 1];

static Element find_element(const char *ref) {
	for (auto i = 0; i < MAP_SIZE; ++i) {
		if (!strcmp(ref, map[i].ref))
			return (map[i]);
	}
}

int main(void) {
	long result = 0;
	long total_steps = 1;
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
			if (count == 0)
				strcpy(map[line].ref, &input[i - 3]);
			if (count == 1)
				strcpy(map[line].left, &input[i - 3]);
			if (count == 2)
				strcpy(map[line].right, &input[i - 3]);
			++i;
		}
		++line;
	}
	free(input);

	Element e;
	Element start_point;
	long steps;
	for (auto i = 0; i < MAP_SIZE; ++i) {
		if (map[i].ref[2] != 'A')
			continue;
		e = map[i];
		for (auto k = 0; instructions[k]; ++k)
			e = (instructions[i] == 'R') ? find_element(e.right) : find_element(e.left);
		start_point = e;
		steps = 0;
		do {
			++steps;
			result = 0;
			for (auto k = 0; instructions[k]; ++k) {
				e = (instructions[i] == 'R') ? find_element(e.right) : find_element(e.left);
				++result;
			}
		} while (strcmp(e.ref, start_point.ref));
		total_steps *= steps;
	}

	printf("%ld\n", total_steps * result);

	return (EXIT_SUCCESS);
}