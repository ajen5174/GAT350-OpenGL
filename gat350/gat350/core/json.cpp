#include "json.h"
#include "filesystem.h"
#include <iostream>

bool json::load(const char* filename, rapidjson::Document& document)
{
	bool success = false;

	char* buffer;
	size_t size;

	if (filesystem::read_file(filename, (void**)& buffer, size))
	{
		buffer[size - 1] = 0;
		std::cout << buffer;
		document.Parse(buffer);
		success = document.IsObject();

		filesystem::free_file(buffer);
	}

	return success;
}

bool json::get_int(const rapidjson::Value& value, const char* property_name, int& _int)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsInt() == false)
	{
		return false;
	}

	_int = property.GetInt();

	return true;
}

bool json::get_float(const rapidjson::Value& value, const char* property_name, float& _float)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsDouble() == false)
	{
		return false;
	}

	_float = property.GetFloat();

	return true;
}

bool json::get_string(const rapidjson::Value& value, const char* property_name, std::string& _string)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsString() == false)
	{
		return false;
	}

	_string = property.GetString();

	return true;
}

bool json::get_bool(const rapidjson::Value& value, const char* property_name, bool& _bool)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsBool() == false)
	{
		return false;
	}

	_bool = property.GetBool();

	return true;
}


bool json::get_name(const rapidjson::Value& value, const char* property_name, Name& name)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd())
	{
		return false;
	}

	auto& property = iter->value;
	if (property.IsString() == false)
	{
		return false;
	}

	name = property.GetString();

	return true;
}
