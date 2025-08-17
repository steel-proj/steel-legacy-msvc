#pragma once

#include <string>
#include <map>

#include "../../ast/ast_visitor.h"
#include "../../compilation_pass.h"
#include "../../symbolics/symbol_table.h"

class decleration_collector : public ast_visitor, public compilation_pass {
public:
	decleration_collector(std::shared_ptr<symbol_table> sym_table)
		: sym_table(sym_table), current_function(nullptr), current_constructor(nullptr), current_type(nullptr) {
	}

	void visit(std::shared_ptr<class function_decleration> func) override;
	void visit(std::shared_ptr<class constructor_decleration> constructor) override;
	void visit(std::shared_ptr<class variable_decleration> var) override;
	void visit(std::shared_ptr<class type_decleration> decl) override;

private:
	std::shared_ptr<symbol_table> sym_table;

	std::shared_ptr<function_decleration> current_function;
	std::shared_ptr<constructor_decleration> current_constructor;
	std::shared_ptr<type_decleration> current_type;
};