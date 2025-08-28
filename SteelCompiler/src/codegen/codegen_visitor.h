#pragma once

#include <string>
#include <map>

#include "../parser/ast/ast_visitor.h"

class codegen_visitor : public ast_visitor {
public:
	codegen_visitor()
		: pseudo(""), line(0) {
	}

	inline std::string get_pseudo() const {
		return pseudo;
	}

private:
	void add_instruction(std::string opc);
	void add_label(std::string lbl);

	std::string pseudo;

	std::map<int, function_declaration*> functions;

	size_t line;
};