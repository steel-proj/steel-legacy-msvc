#include "stlib_file.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

stlib_load_error stlib_file::load(const std::string& path) {
	stlib_file lib;
	
	std::ifstream file(path);
	if (!file.is_open()) {
		return STLIB_FILE_UNOPENED;
	}
	
	std::string magic;
	magic.resize(4);
	file.read(magic.data(), 4);
	if (magic != STLIB_MAGIC) {
		return STLIB_INVALID_FORMAT;
	}
	
	lib.lib_name = file["name"].value_or("unknown");
	lib.lib_version = file["version"].value_or("unknown");
	lib.lib_type = file["type"].value_or("unknown");

	if (auto sources = file["sources"].as_array()) {
		for (const auto& source : *sources) {
			if (source.is_string()) {
				auto full_path = root / source.as_string()->get();
				lib.sources.push_back(source_file(full_path.string()));
			}
		}
	}
	return lib;
}
