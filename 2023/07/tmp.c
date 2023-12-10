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
//
// 
// 2 0
// 3 1
// 4 2
// 5 3
// 6 4
// 7 5
// 8 6
// 9 7
// T 8
// J 9
// Q 10
// K 11
// A 12

#define auto __auto_type

enum Type { HIGH, ONE_PAIR, TWO_PAIR, TRIAD, FULL, FOUR, FIVE };

typedef struct {
	char *value;
	int bid;
	int type;
} Hand;

// void sort_hand(char *hand) {
// 	const auto order = "AKQT98765432J";
// 	char tmp;
// 	for (int truc = 0; truc < 69; ++truc) { //kdx.re tips
// 		auto pos = 0;
// 		for (auto i = 0; order[i]; ++i) {
// 			for (auto j = pos; hand[j]; ++j) {
// 				if (hand[j] == order[i]) {
// 					++pos;
// 					continue;
// 				}
// 				for (auto k = j + 1; hand[k]; ++k) {
// 					if (hand[k] == order[i]) {
// 						tmp = hand[j];
// 						hand[j] = hand[k];
// 						hand[k] = tmp;
// 						++pos;
// 					}
// 				}
// 			}
// 		}
// 	}
// }

int find_type(const char *hand) {

	for (auto i = 0; hand[i]; ++i) {
		if (hand[i] == 'J')
			++joker;
	}
	// printf("joker %d\n", joker);
	for (auto i = 0; hand[i]; ++i) {
		auto k = i;
		while (hand[k] == hand[i])
			++k;
		switch (k - i) {
			case 5:
				return (FIVE);
				break;
			case 4:
				if (joker)
					return (FIVE);
				return (FOUR);
				break;
			case 3: {
				if (joker == 2)
					return (FIVE);
				else if (joker)
					return (FOUR);
				triad = 1;
				i = k - 1;
				break;
			}
			case 2: {
				if (joker == 3)
					return (FIVE);
				else if (joker == 2)
					return (FOUR);
				else if (joker) {
					triad = 1;
					joker = 0;
					break;
				}
				if (pair)
					return TWO_PAIR;
				pair = 1;
				i = k - 1;
				break;
			}
		}
		if (hand[k] == '\0')
			break;
	}
	for (auto i = 0; hand[i]; ++i) {
		if (hand[i] == 'J')
			++joker;
	}
	if (triad && pair)
		return (FULL);
	else if (triad)
		return (TRIAD);
	else if (pair || joker)
		return (ONE_PAIR);
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
	// auto card = 0;
	int i;
	char *input = NULL;
	size_t size;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		// for (int i = 0; input[i] != ' '; ++i) {
		// 	if (isdigit(input[i])) {
		// 		hands[line].values[card] = atoi(&input[i]);
		// 		++card;
		// 	}
		// 	while (isdigit(input[i]))
		// 		++i;
		// }
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
		// printf("%s %d: %d\n", hands[i].ordered, hands[i].bid, hands[i].type); //hands[i].bid * (i + 1));
		printf("%s %d\n", hands[i].value, hands[i].bid);
		result += hands[i].bid * (i + 1);
		free(hands[i].value);
	}

	printf("%u\n", result);

	return (EXIT_SUCCESS);
}
