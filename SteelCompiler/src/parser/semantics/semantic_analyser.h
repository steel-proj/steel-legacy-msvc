#pragma once

#include "../compilation_pass.h"
#include "../ast/ast.h"
#include "../symbolics/symbol_table.h"

class semantic_analyser : public compilation_pass {
public:
	semantic_analyser(std::shared_ptr<program> prog, std::shared_ptr<symbol_table> sym_table)
		: program(prog), sym_table(sym_table) {
	}

	void analyse();

private:
	std::shared_ptr<program> program;
	std::shared_ptr<symbol_table> sym_table;
};