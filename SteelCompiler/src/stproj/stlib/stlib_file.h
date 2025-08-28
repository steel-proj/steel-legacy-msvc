#pragma once

#include <vector>
#include <string>

#include "../../parser/modules/module_manager.h"

constexpr auto STLIB_MAGIC = "SLIB";

enum stlib_load_error {
	STLIB_OK,
	STLIB_FILE_UNOPENED,
	STLIB_INVALID_FORMAT,
};

class stlib_file {
public:
	stlib_file() = default;

	stlib_load_error load(const std::string& path);
	void save(const std::string& path);

	std::string lib_name;
	std::string lib_version;
	std::string lib_author;
	std::string code;

private:
};