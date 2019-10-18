#pragma once

#include "types.h"
#include <string>

class Name
{
public:
	Name() : m_id(0), m_index(0) {}
	Name(const char* string, bool unique = false);

	bool operator == (const Name& other) const;
	bool operator != (const Name& other) const;
	bool operator  < (const Name& other) const;

	std::string ToString() const;
	const char* c_str() const;

	size_t GetID() const { return m_id; }

	static void AllocNames();
	static void FreeNames();

private:
	size_t m_id;
	size_t m_index;

	static const size_t MAX_ENTRIES = 65536;
	static const size_t MAX_NAME_SIZE = 64;
	
	static size_t ms_unique_id;
	static char* ms_names;
};

