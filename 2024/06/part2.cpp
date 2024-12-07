#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static std::vector<int> split_to_int(const std::string &s, char sep)
{
	std::vector<int> array;
	std::string e;

	for (auto i = 0; s[i]; i++) {
		if (s[i] == sep) {
			if (!e.empty()) {
				array.push_back(atoi(e.c_str()));
				e.clear();
			}
			continue;
		}
		e += s[i];
	}
	if (!e.empty())
		array.push_back(atoi(e.c_str()));
	return array;
}

int main(void)
{
	int result = 0;
	std::string input;
	std::vector<std::pair<int, int>> rules;
	std::vector<std::vector<int>> pages;

	while (std::getline(std::cin, input)) {
		if (input.empty())
			break;
		int a = atoi(input.c_str());
		input.erase(0, 3);
		int b = atoi(input.c_str());
		rules.push_back({a, b});
	}
	while (std::getline(std::cin, input))
		pages.push_back(split_to_int(input, ','));

	for (auto line : pages) {
		bool uwu = false;
		for (auto i = 0; i < line.size(); i++) {
			for (auto rule : rules) {
				auto a = std::find(line.begin(), line.end(),
				                   rule.first);
				auto b = std::find(line.begin(), line.end(),
				                   rule.second);
				if (a == line.end() || b == line.end())
					continue;
				if (a < b)
					continue;
				auto cramptés = *a;
				line.erase(a);
				line.insert(line.begin(), cramptés);
				uwu = true;
			}
		}
		if (uwu)
			result += line[line.size() / 2];
	}

	printf("%d\n", result);

	return EXIT_SUCCESS;
}
