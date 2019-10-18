#include "string.h"
#include <string>
#include <sstream>

void string_to_lower(const char* source, char* destination, size_t size)
{
	strcpy_s(destination, size, source);
	for (size_t i = 0; i < strlen(destination); i++)
	{
		destination[i] = std::tolower(destination[i]);
	}
}

void tokenize(const std::string& string, char delimiter, std::vector<std::string>& strings)
{
	std::stringstream stream(string);
	
	std::string s;
	while (std::getline(stream, s, delimiter))
	{
		strings.push_back(s);
	}
}

bool compare_char(char c1, char c2)
{
	return (c1 == c2) || (std::toupper(c1) == std::toupper(c2));
}

bool string_compare_no_case(std::string& string1, std::string& string2)
{
	return ((string1.size() == string2.size()) && std::equal(string1.begin(), string1.end(), string2.begin(), &compare_char));
}
