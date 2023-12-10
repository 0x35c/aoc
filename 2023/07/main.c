#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Five of a kind AAAAA
// Four of a kind AA8AA
// Full house 3 + 2 23332
// Three of a kind TTT98
// Two pair 23432
// One pair A23A4
// High card 23456 (everything different)

#define auto __auto_type

enum Type { HIGH, PAIR, TWO_PAIR, TRIAD, FULL, FOUR, FIVE };

typedef struct {
	char *value;
	int bid;
	int type;
} Hand;

int count_char(const char *hand, char c) {
	int count = 0;
	for (auto i = 0; hand[i]; ++i) {
		if (hand[i] == c)
			++count;
	}
	return (count);
}

int find_type(const char *hand) {
	const auto order = "AKQT98765432J";
	int weights[13] = {0};
	for (auto i = 0; order[i]; ++i)
		weights[i] = count_char(hand, order[i]);
	int tmp = -1;
	int pos = 0;
	for (auto i = 0; i < 13; ++i) {
		if (weights[i] > tmp && order[i] != 'J') {
			tmp = weights[i];
			pos = i;
		}
	}
#ifdef DEBUG
	printf("%s weights[pos]: %d\n", hand, weights[pos]);
#endif
	weights[pos] += weights[12];
#ifdef DEBUG
	printf("%s weights[pos]: %d at %c\n", hand, weights[pos], order[pos]);
#endif
	int pair = 0;
	int triad = 0;
	for (auto i = 0; order[i] != 'J'; ++i) {
		switch (weights[i])
		{
			case 5:
				return (FIVE);
			case 4:
				return (FOUR);
			case 3:
				triad = 1;
				break;
			case 2: {
				if (pair)
					return (TWO_PAIR);
				pair = 1;
				break;
			}
			default:
				break;
		}
	}
	if (triad && pair)
		return (FULL);
	if (triad)
		return (TRIAD);
	if (pair)
		return (PAIR);
	return (HIGH);
}

int find_strongest(Hand *hands, int first, int second) {
	const auto order = "AKQT98765432J";
	auto i = 0;
	while (hands[first].value[i] == hands[second].value[i])
		++i;
	for (auto k = 0; order[k]; ++k) {
		if (hands[first].value[i] == order[k])
			return (first);
		else if (hands[second].value[i] == order[k])
			return (second);
	}
	return (0);
}

void sort_hands(Hand *hands) {
	Hand tmp;
	for (auto i = 0; hands[i].bid; ++i) {
		for (auto k = i + 1; hands[k].bid; ++k) {
			if (hands[k].type < hands[i].type) {
				tmp = hands[i];
				hands[i] = hands[k];
				hands[k] = tmp;
			}
			else if (hands[k].type == hands[i].type && find_strongest(hands, k, i) == i) {
				tmp = hands[i];
				hands[i] = hands[k];
				hands[k] = tmp;
			}
		}
	}
}

int main(void) {
	Hand hands[1001] = {0};
	unsigned result = 0;
	auto line = 0;
	int i;
	char *input = NULL;
	size_t size;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		for (i = 0; input[i] != ' '; ++i);
		input[i] = '\0';
		hands[line].value = strdup(input);
		++i;
		hands[line].bid = atoi(&input[i]);
		i = 0;
		++line;
	}
	free(input);

	for (i = 0; hands[i].bid; ++i) {
		hands[i].type = find_type(hands[i].value);
	}
	sort_hands(hands);
	for (i = 0; hands[i].bid; ++i) {
#ifdef DEBUG
		printf("%s %d: %d\n", hands[i].value, hands[i].bid, hands[i].type); //hands[i].bid * (i + 1));
#else
		printf("%s %d\n", hands[i].value, hands[i].bid);
#endif
		result += hands[i].bid * (i + 1);
		free(hands[i].value);
	}
	printf("%u\n", result);

	return (EXIT_SUCCESS);
}
