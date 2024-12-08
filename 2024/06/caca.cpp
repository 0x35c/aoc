#include "../utils.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define CELL() map[y][x]

enum {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	START,
	IVENEVERPUTMYASSHERE,
	IVEPUTMYASSHERE,
	OBS
};

static void print_map(const std::vector<std::vector<int>> &map)
{
	auto y = 0;
	std::cout << "  0123456789" << std::endl;
	for (auto line : map) {
		std::cout << y++ << ' ';
		for (auto c : line) {
			switch (c) {
			case UP:
				std::cout << '^';
				break;
			case RIGHT:
				std::cout << '>';
				break;
			case DOWN:
				std::cout << 'v';
				break;
			case LEFT:
				std::cout << '<';
				break;
			case START:
				std::cout << 'X';
				break;
			case IVENEVERPUTMYASSHERE:
				std::cout << '.';
				break;
			case IVEPUTMYASSHERE:
				std::cout << 'X';
				break;
			case OBS:
				std::cout << '#';
				break;
			default:
				std::cout << c;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

static void fill_map(std::vector<std::vector<int>> &map, std::string input)
{
	std::vector<int> translated;
	for (auto c : input) {
		if (c == '.')
			translated.push_back(IVENEVERPUTMYASSHERE);
		else if (c == '#')
			translated.push_back(OBS);
		else if (c == '^')
			translated.push_back(START);
	}
	map.push_back(translated);
}

static bool check_loop(const std::vector<std::vector<int>> &map, int x, int y,
                       int direction)
{
	const size_t width = map[0].size();
	const size_t height = map.size();

	switch (direction % 4) {
	case UP: {
		if (x >= width - 1)
			return false;
		/* if (map[y][x + 1] != RIGHT && map[y][x + 1] != DOWN) */
		/* 	return false; */
		bool uwu = false;
		for (auto X = x + 1; X < map[y].size(); X++) {
			if (map[y][X] == RIGHT ||
			    (map[y][X] == DOWN && map[y + 1][X] == OBS))
				uwu = true;
			if (map[y][X] == OBS && uwu)
				return true;
		}
	}
	case RIGHT: {
		if (y >= height - 1)
			return false;
		/* if (map[y + 1][x] != DOWN && map[y + 1][x] != LEFT) */
		/* 	return false; */
		bool uwu = false;
		for (auto Y = y + 1; Y < map.size(); Y++) {
			if (map[Y][x] == DOWN ||
			    (map[Y][x] == LEFT && map[Y][x - 1] == OBS))
				uwu = true;
			if (map[Y][x] == OBS && uwu)
				return true;
		}
	}
	case DOWN: {
		if (x < 1)
			return false;
		/* if (map[y][x - 1] != LEFT && map[y][x - 1] != UP) */
		/* 	return false; */
		bool uwu = false;
		for (auto X = x - 1; X >= 0; X--) {
			if (map[y][X] == LEFT ||
			    (map[y][X] == UP && map[y - 1][X] == OBS))
				uwu = true;
			if (map[y][X] == OBS && uwu)
				return true;
		}
	}
	case LEFT: {
		if (y < 1)
			return false;
		/* if (map[y - 1][x] != UP && map[y - 1][x] != RIGHT) */
		/* 	return false; */
		bool uwu = false;
		for (auto Y = y - 1; Y >= 0; Y--) {
			if (map[Y][x] == UP ||
			    (map[Y][x] == RIGHT && map[Y][x + 1] == OBS))
				uwu = true;
			if (map[Y][x] == OBS && uwu)
				return true;
		}
	}
	}
	return false;
}

static int move_guard(std::vector<std::vector<int>> &map, int x, int y)
{
	int direction = UP;
	int count = 0;

	while (1) {
		switch (direction % 4) {
		case UP: {
			while (y >= 0 && CELL() != OBS) {
				CELL() = UP;
				if (check_loop(map, x, y, UP)) {
					printf("x: %d - y: %d\n", x, y);
					CELL() = IVEPUTMYASSHERE;
					print_map(map);
					CELL() = UP;
					count++;
				}
				y--;
			}
			if (y < 0)
				return count;
			y++;
			direction++;
		}
		case RIGHT: {
			while (x < map[y].size() && CELL() != OBS) {
				CELL() = RIGHT;
				if (check_loop(map, x, y, RIGHT)) {
					printf("x: %d - y: %d\n", x, y);
					CELL() = IVEPUTMYASSHERE;
					print_map(map);
					CELL() = RIGHT;
					count++;
				}
				x++;
			}
			if (x >= map[y].size())
				return count;
			x--;
			direction++;
		}
		case DOWN: {
			while (y < map.size() && CELL() != OBS) {
				CELL() = DOWN;
				if (check_loop(map, x, y, DOWN)) {
					printf("x: %d - y: %d\n", x, y);
					CELL() = IVEPUTMYASSHERE;
					print_map(map);
					CELL() = DOWN;
					count++;
				}
				y++;
			}
			if (y >= map.size())
				return count;
			y--;
			direction++;
		}
		case LEFT: {
			while (x >= 0 && CELL() != OBS) {
				CELL() = LEFT;
				if (check_loop(map, x, y, LEFT)) {
					printf("x: %d - y: %d\n", x, y);
					CELL() = IVEPUTMYASSHERE;
					print_map(map);
					CELL() = LEFT;
					count++;
				}
				x--;
			}
			if (x < 0)
				return count;
			x++;
			direction++;
		}
		}
	}
	return count;
}

int main(void)
{
	int result = 0;
	std::string input;
	std::vector<std::vector<int>> map;

	while (std::getline(std::cin, input)) {
		if (input.empty())
			break;
		fill_map(map, input);
	}

	for (auto y = 0; y < map.size(); y++)
		for (auto x = 0; x < map[y].size(); x++)
			if (map[y][x] == START)
				result = move_guard(map, x, y);

	/* for (auto line : map) */
	/* 	for (auto c : line) */
	/* 		result += (c == IVEPUTMYASSHERE) ? 1 :
	 * 0; */

	printf("%d\n", result);

	return EXIT_SUCCESS;
}
