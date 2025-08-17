#pragma once

#include <string>

enum error_type {
	ERR_ERROR,
	ERR_WARNING,
	ERR_INFO,
};

class error {
public:
	error(const std::string& code, const std::string& message, size_t line, size_t column, error_type type = ERR_ERROR)
		: code(code), message(message), line(0), column(0), type(type) {
	}

	std::string code;
	std::string message;
	size_t line, column;
	error_type type;
};