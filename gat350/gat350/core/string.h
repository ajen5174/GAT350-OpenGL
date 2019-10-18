#pragma once
#include "core.h"

void string_to_lower(const char* source, char* destination, size_t size);
void tokenize(const std::string& string, char delimiter, std::vector<std::string>& strings);
bool string_compare_no_case(std::string& string1, std::string& string2);