#include "interpreter.h"

#include "interpreter_visitor.h"

void interpreter::begin_execution() {
	interpreter_visitor visitor(sym_table);
	program->accept(visitor);
}

void interpreter::add_builtin_function(const std::string& identifier, type_ptr return_type, const std::vector<std::shared_ptr<variable_decleration>>& parameters) {
	function_decleration decl = { return_type, identifier, parameters, {} };
	sym_table->add_function(std::make_shared<function_decleration>(decl));
}