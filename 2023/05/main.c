#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define auto __auto_type
#define SEEDS (sizeof(seeds) / sizeof(seeds[0]))
#define MAP_SIZE 190

typedef struct {
	long dest;
	long src;
	long range;
} Transform;

Transform map[190] = {0};
long seeds[] = { 3127166940, 109160474, 3265086325, 86449584, 1581539098, 205205726, 3646327835, 184743451, 2671979893, 17148151, 305618297, 40401857, 2462071712, 203075200, 358806266, 131147346, 1802185716, 538526744, 635790399, 705979250 };

int main(void) {
	long result = __LONG_MAX__;
	char *input = NULL;
	size_t size;
	int i = 0;
	int count = 0;
	while (1) {
		const auto rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		if (!strcmp("\n", input)) {
			++count;
			continue;
		}
		(map[count]).dest = atol(&input[i]);
		for (;isdigit(input[i]); ++i);
		++i;
		(map[count]).src = atol(&input[i]);
		for (;isdigit(input[i]); ++i);
		++i;
		(map[count]).range = atol(&input[i]);
		++count;
		i = 0;
	}
	map[count].range = -1;
	free(input);

	for (auto i = 0; i < SEEDS; i += 2) {
		printf("%d\n", i);
		for (long kdx = 0; kdx < seeds[i + 1]; ++kdx) {
			long seed = kdx + seeds[i];
			for (int j = 0; map[j].range != -1; ++j) {
				const auto m = &map[j];
				if (!m->range)
					continue;
				if (m->src + m->range > seed && seed >= m->src) {
					seed += m->dest - m->src;
					while (m->range) // be happy kdx
						++j;
				}
			}
			if (seed < result)
				result = seed;
		}
	}
	printf("%ld\n", result);

	return (EXIT_SUCCESS);
}