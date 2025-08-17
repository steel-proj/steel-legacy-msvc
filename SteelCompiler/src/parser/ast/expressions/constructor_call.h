#pragma once

#include <string>
#include <memory>

#include "expression.h"
#include "../declerations/function_decleration.h"
#include "../declerations/type_decleration.h"
#include "../../parser_utils.h"
#include "../../types/types.h"

class constructor_call : public expression, public std::enable_shared_from_this<constructor_call> {
public:
	ENABLE_ACCEPT(constructor_call)

	constructor_call(std::string type_name, std::vector<std::shared_ptr<expression>> args)
		: type_name(type_name), args(args) {
	}

	std::string string(int indent) const override {
		std::string ind = indent_s(indent);
		std::string result = ind + "Constructor Call: \"" + type_name + "\"\n";
		result += ind + " Arguments:\n";
		if (args.size() <= 0) {
			result += ind + "  <None>\n";
		}
		else {
			for (int i = 0; i < args.size(); i++) {
				result += args[i]->string(indent + 1) + "\n";
			}
		}
		return result;
	}

	type_ptr type() const override {
		return type_decl->type();
	}
	bool is_rvalue() const override {
		// constructor calls always return a temporary value
		// (unless stored in a variable, which does not apply here)
		return true;
	}

	inline std::vector<type_ptr> get_arg_types() const {
		std::vector<type_ptr> types;
		for (const auto& arg : args) {
			types.push_back(arg->type());
		}
		return types;
	}

	std::string type_name;
	std::vector<std::shared_ptr<expression>> args;
	std::shared_ptr<constructor_decleration> decleration;
	std::shared_ptr<type_decleration> type_decl;
};