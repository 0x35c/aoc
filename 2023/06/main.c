#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RACES 1
#define TIME races[race][0]
#define DISTANCE races[race][1]

int main(void) {
	long result = 1;
	long races[RACES][2] = { { 40828492, 233101111101487 } };
	long count = 0;

	for (long race = 0; race < RACES; ++race) {
		for (long speed = 0; speed < TIME; ++speed) {
			if (speed * (TIME - speed) > DISTANCE)
				++count;
		}
		result *= count;
		count = 0;
	}

	printf("%ld\n", result);

	return (EXIT_SUCCESS);
}
