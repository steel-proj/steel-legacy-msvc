#pragma once

#include <vector>
#include <string>
#include <memory>

#include "../parser/ast/ast.h"
#include "../parser/symbolics/symbol_table.h"

class interpreter {
public:
	interpreter(std::shared_ptr<program> prog, std::shared_ptr<symbol_table> sym_table)
		: program(prog), sym_table(sym_table) {
	}

	void begin_execution();
	void add_builtin_function(const std::string& identifier, type_ptr return_type, const std::vector<std::shared_ptr<variable_decleration>>& parameters);

private:
	std::shared_ptr<program> program;
	std::shared_ptr<symbol_table> sym_table;
};