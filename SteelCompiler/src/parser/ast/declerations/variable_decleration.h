#pragma once

#include <string>

#include "../ast_node.h"
#include "../expressions/expression.h"
#include "../../types/types.h"

class variable_decleration : public ast_node, public std::enable_shared_from_this<variable_decleration> {
public:
	ENABLE_ACCEPT(variable_decleration)

	variable_decleration(type_ptr type, std::string identifier)
		: type(type), identifier(identifier), initializer(nullptr) {
	}
	variable_decleration(type_ptr type, std::string identifier, std::shared_ptr<expression> initializer)
		: type(type), identifier(identifier), initializer(initializer), initialized(initializer) {
	}

	std::string string(int indent) const override {
		std::string ind = indent_s(indent);
		std::string result = ind + "Variable Declaration:\n";
		result += ind + " Type: " + type->type_name() + "\n";
		result += ind + " Identifier: " + identifier + "\n";
		result += ind + " Initializer:\n";
		if (initializer) {
			result += initializer->string(indent + 1) + "\n";
		}
		else {
			result += ind + "  <None>\n";
		}
		return result;
	}

	inline bool has_initializer() const {
		return initializer != nullptr;
	}

	type_ptr type;
	std::string identifier;
	std::shared_ptr<expression> initializer;
	bool initialized = false;
	bool is_parameter = false;
};