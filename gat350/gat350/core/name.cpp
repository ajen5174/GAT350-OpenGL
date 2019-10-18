#include "name.h"
#include "assert.h"
#include "string.h"

size_t Name::ms_unique_id = 0;
char* Name::ms_names = nullptr;

Name::Name(const char* string, bool unique)
{
	ASSERT(strlen(string) < MAX_NAME_SIZE);

	char string_lower[MAX_NAME_SIZE];
	string_to_lower(string, string_lower, MAX_NAME_SIZE);

	if (unique)
	{
		std::string unique_string(string_lower);
		unique_string += std::to_string(ms_unique_id);
		ms_unique_id++;

		m_id = static_cast<u32>(std::hash<std::string>{}(unique_string.c_str()));
		m_index = m_id % MAX_ENTRIES;
		strcpy_s(ms_names + (m_index * MAX_NAME_SIZE), MAX_NAME_SIZE, unique_string.c_str());
	}
	else
	{
		m_id = static_cast<u32>(std::hash<std::string>{}(string_lower));
		m_index = m_id % MAX_ENTRIES;
		strcpy_s(ms_names + (m_index * MAX_NAME_SIZE), MAX_NAME_SIZE, string);
	}
}

bool Name::operator==(const Name& other) const
{
	return (m_id == other.m_id);
}

bool Name::operator!=(const Name& other) const
{
	return (m_id != other.m_id);
}

bool Name::operator<(const Name& other) const
{
	return (m_id < other.m_id);
}

std::string Name::ToString() const
{
	return std::string(c_str());
}

const char* Name::c_str() const
{
	return ms_names + (m_index * MAX_NAME_SIZE);
}

void Name::AllocNames()
{
	ms_names = new char[MAX_ENTRIES * MAX_NAME_SIZE];
}

void Name::FreeNames()
{
	delete ms_names;
}
