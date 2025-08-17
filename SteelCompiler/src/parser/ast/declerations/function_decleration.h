#pragma once

#include <string>
#include <vector>

#include "variable_decleration.h"
#include "../ast_node.h"
#include "../../parser_utils.h"
#include "../../types/types.h"

class function_decleration : public ast_node, public std::enable_shared_from_this<function_decleration> {
public:
	ENABLE_ACCEPT(function_decleration)

	function_decleration(type_ptr return_type, std::string identifier, std::vector<std::shared_ptr<variable_decleration>> parameters)
		: return_type(return_type), identifier(identifier), parameters(parameters), body(nullptr) /* for built in functions */ {
	}
	function_decleration(type_ptr return_type, std::string identifier, std::vector<std::shared_ptr<variable_decleration>> parameters, ast_ptr body)
		: return_type(return_type), identifier(identifier), parameters(parameters), body(body) {
	}

	std::string string(int indent) const override {
		std::string ind = indent_s(indent);
		std::string result = ind + "Function Declaration: \"" + identifier + "\"\n";
		result += ind + " Type: " + return_type->type_name() + "\n";
		result += ind + " Parameters:\n";
		if (parameters.empty()) {
			result += ind + "  <None>\n";
		}
		else {
			for (int i = 0; i < parameters.size(); i++) {
				const auto& param = parameters[i];
				result += ind + "  - " + param->type->type_name() + " " + param->identifier + "\n";
			}
		}
		if (body) {
			result += ind + " Body:\n";
			result += body->string(indent + 1);
		}
		else {
			result += ind + " Body: Not defined\n";
		}
		return result;
	}

	std::vector<type_ptr> get_expected_types() {
		std::vector<type_ptr> expected_types;
		for (const auto& param : parameters) {
			expected_types.push_back(param->type);
		}
		return expected_types;
	}

	type_ptr return_type;
	std::string identifier;
	std::vector<std::shared_ptr<variable_decleration>> parameters;
	ast_ptr body;
	bool is_method = false;
};