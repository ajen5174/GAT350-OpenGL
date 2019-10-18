#pragma once
#include <string>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING //lol

namespace filesystem
{
	bool file_exists(const char* filename);
	bool file_size(const char* filename, size_t& size);

	bool read_file(const char* filename, void** buffer, size_t& size);
	bool read_file(const char* filename, std::string& string);
	bool write_file(const char* filename, void* buffer, size_t size);
	void free_file(void* buffer);

	bool delete_file(const char* filename);
	bool copy_file(const char* source, const char* destination, bool overwrite = true);

	bool directory_exists(const char* directory);
	bool copy_directory(const char* source, const char* destination, bool recursive = true);
	void create_directory(const char* directory);
	bool delete_directory(const char* directory);
	void delete_empty_directory(const char* directory);

	void set_current_path(const char* pathname);
	void get_current_path(char* pathname, size_t size);
}