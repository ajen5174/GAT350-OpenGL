#pragma once

#ifndef NDEBUG
	#define ASSERT(expression) _assert(expression, #expression,__FILE__, __LINE__, __func__)
	#define ASSERT_MSG(expression, message) _assert(expression, #expression,__FILE__, __LINE__, __func__, message)
#else
	#define ASSERT(expression)
	#define ASSERT_MSG(expression, message)
#endif

void _assert(bool expression, const char* expression_string, const char* filename, int line, const char* function_name);
void _assert(bool expression, const char* expression_string, const char* filename, int line, const char* function_name, const char* message);