#include <string>
#include <vector>

std::vector<int> split_to_int(const std::string &s, char sep)
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

std::vector<std::string> split(const char *s, char sep)
{
	std::vector<std::string> array;
	std::string e;

	for (auto i = 0; s[i]; i++) {
		if (s[i] == sep) {
			if (!e.empty()) {
				array.push_back(e);
				e.clear();
			}
			continue;
		}
		e += s[i];
	}
	if (!e.empty())
		array.push_back(e);
	return array;
}
