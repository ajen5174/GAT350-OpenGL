#include "assert.h"

#include <iostream>

void _assert(bool expression, const char* expression_string, const char* filename, int line, const char* function_name)
{
	if (expression == false)
	{
		std::cout << "assertion failed: " << expression_string << std::endl;
		std::cout << "source: " << filename << std::endl;
		std::cout << "line: " << line << std::endl;
		std::cout << "function: " << function_name << std::endl;
		abort();
	}
}

void _assert(bool expression, const char* expression_string, const char* filename, int line, const char* function_name, const char* message)
{
	if (expression == false)
	{
		std::cout << "assertion failed: " << expression_string << std::endl;
		std::cout << message << std::endl;
		std::cout << "source: " << filename << std::endl;
		std::cout << "line: " << line << std::endl;
		std::cout << "function: " << function_name << std::endl;
		abort();
	}
}
