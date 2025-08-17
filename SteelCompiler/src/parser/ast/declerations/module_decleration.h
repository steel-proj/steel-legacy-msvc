#pragma once

#include <string>

#include "../ast_node.h"

class module_decleration : public ast_node, public std::enable_shared_from_this<module_decleration> {
public:
	ENABLE_ACCEPT(module_decleration)

	module_decleration(std::string name, ast_ptr body)
		: name(name), body(body) {
	}

	std::string string(int indent) const override {
		std::string ind = indent_s(indent);
		std::string result = ind + "Module Decleration: \"" + name + "\"\n";
		return result;
	}

	std::string name;
	ast_ptr body;
};