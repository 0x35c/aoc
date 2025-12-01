#pragma once

#include <string>
#include <vector>

std::vector<std::string> split(const char *s, char sep);
std::vector<int> split_to_int(const std::string &s, char sep);
std::vector<long> split_to_long(const std::string &s, char sep);
