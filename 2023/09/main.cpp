#include <string>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

static bool check_zero(vector<int> values) {
	int count = 0;
	for (auto e : values) {
		if (e != 0)
			return (false);
	}
	return (true);
}

int main(void) {
	int result = 0;
	char *input = NULL;
	size_t size;
	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		vector<vector<int>> values;
		values.push_back({});
		for (auto tok = strtok(input, " \n"); tok; tok = strtok(NULL, " \n")) {
			values[0].push_back(atoi(tok));
		}
		int count = 0;
		while (!check_zero(values[count])) {
			values.push_back({});
			for (auto i = 0; i < values[count].size() - 1; ++i) {
				values[count + 1].push_back(values[count][i + 1] - values[count][i]);
			}
			++count;
		}
		values[count].insert(values[count].begin(), 0);
		while (count > 0) {
			values[count - 1].insert(values[count - 1].begin(), -values[count].front() + values[count - 1].front());
			--count;
		}
		result += values[0].front();
	}
	free(input);

	std::cout << result << std::endl;

	return (EXIT_SUCCESS);
}
