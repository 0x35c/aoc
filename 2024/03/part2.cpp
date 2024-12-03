#include <iostream>
#include <regex>
#include <string.h>
#include <string>

static int mul(std::string a, std::string b)
{
	return atoi(a.c_str()) * atoi(b.c_str());
}

int main(void)
{
	int result = 0;
	char *input = NULL;
	size_t size;
	int operate;

	while (1) {
		int rv = getline(&input, &size, stdin);
		if (rv < 1)
			break;
		std::string line = input;
		std::regex regexp("mul\\(([0-9]{0,3})\\,([0-9]{0,3})\\)|do\\("
		                  "\\)|don\'t\\(\\)");
		std::smatch matches;
		std::string::const_iterator searchStart(line.cbegin());
		while (
		    regex_search(searchStart, line.cend(), matches, regexp)) {
			if (matches[0] == "don't()")
				operate = 0;
			else if (matches[0] == "do()")
				operate = 1;
			else if (operate)
				result += mul(matches[1], matches[2]);
			searchStart = matches.suffix().first;
		}
	}
	free(input);

	printf("%d\n", result);

	return EXIT_SUCCESS;
}
