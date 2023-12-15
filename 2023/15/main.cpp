#include <string>
#include <string.h>
#include <iostream>
#include <vector>

typedef struct {
	std::string label;
	int focal;
} Lens;

static void split(const std::string& str, char sep, std::vector<std::string> &dest);
static void find_lens(const std::vector<std::vector<Lens>> &boxes, const std::string &label);
static void parse_lenses(std::vector<std::string> &lenses, std::vector<std::vector<Lens>> &boxes);
static int hash_string(const std::string &str);

static void split(const std::string& str, char sep, std::vector<std::string> &dest)
{
	std::string token;

	for (auto c : str) {
		if (c == sep)	{
			dest.push_back(token);
			token.clear();
		}
		else
			token += c; 
	}
	dest.push_back(token);
}

static int find_lens(const std::vector<Lens> &box, const std::string &label)
{
	for (auto i = 0; i < box.size(); i++) {
		if (label == box[i].label)
			return (i);
	}
	return (-1);
}

static void parse_lenses(std::vector<std::string> &lenses, std::vector<std::vector<Lens>> &boxes)
{
	for (auto i = 0; i < lenses.size(); i++) {
		auto lens = lenses[i];
		std::string label;
		auto k = 0;
		while (auto c = lens[k]) {
			if (c == '=' || c == '-')
				break;
			label += c;
			k++;
		}

		int box_pos = hash_string(label);
		std::vector<Lens> &box = boxes[box_pos];
		if (lens[k] == '=') {
			int pos = find_lens(box, label);
			if (pos != -1) {
				box[pos].label = label;
				box[pos].focal = lens[k + 1] - '0';
			}
			else {
				Lens lens_node = { label, lens[k + 1] - '0'};
				box.push_back(lens_node);
			}
		}
		else {
			int pos = find_lens(box, label);
			if (pos != -1)
				box.erase(box.begin() + pos);
		}
	}
}

static int hash_string(const std::string &str)
{
	int value = 0;
	for (auto c : str) {
		value += c;
		value *= 17;
		value %= 256;
	}
	return (value);
}

int main(void)
{
	int result = 0;
	char *input = NULL;
	size_t size;
	std::vector<std::string> strings;
	std::vector<std::vector<Lens>> boxes;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		split(input, ',', strings);
	}
	free(input);

	for (auto i = 0; i < 256; i++)
		boxes.push_back({});

	parse_lenses(strings, boxes);
	for (auto i = 0; i < boxes.size(); i++) {
		for (auto k = 0; k < boxes[i].size(); k++) {
			result += (i + 1) * (k + 1) * boxes[i][k].focal;
		}
	}

	// This is part 1
	// for (auto el : strings) {
	// 	if (el.empty())
	// 		continue;
	// 	result += hash_string(el);
	// 	printf("%s => %d\n", el.c_str(), hash_string(el));
	// }

	printf("%d\n", result);

	return (EXIT_SUCCESS);
}
