#include <string>
#include <string.h>
#include <iostream>
#include <vector>

static void split(const std::string& str, char sep, std::vector<std::string> &dest){
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

static int hash_string(const std::string &str) {
	int value = 0;
	for (auto c : str) {
		value += c;
		value *= 17;
		value %= 256;
	}
	return (value);
}

int main(void) {
	int result = 0;
	char *input = NULL;
	size_t size;
	std::vector<std::string> strings;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		split(input, ',', strings);
	}
	free(input);

	for (auto e : strings) {
		if (e.empty())
			continue;
		result += hash_string(e);
		printf("%s => %d\n", e.c_str(), hash_string(e));
	}

	printf("%d\n", result);

	return (EXIT_SUCCESS);
}
