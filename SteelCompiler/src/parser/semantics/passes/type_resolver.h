#pragma once

#include <string>
#include <map>

#include "../../ast/ast_visitor.h"
#include "../../compilation_pass.h"
#include "../../symbolics/symbol_table.h"

class type_resolver : public ast_visitor, public compilation_pass {
public:
	type_resolver(std::shared_ptr<symbol_table> sym_table)
		: sym_table(sym_table) {
	}

	void visit(std::shared_ptr<class function_decleration> func) override;
	void visit(std::shared_ptr<class constructor_decleration> constructor) override;
	void visit(std::shared_ptr<class variable_decleration> var) override;
	void visit(std::shared_ptr<class type_decleration> decl) override;
	void visit(std::shared_ptr<class function_call> func_call) override;
	void visit(std::shared_ptr<class constructor_call> constructor_call) override;

private:
	std::shared_ptr<symbol_table> sym_table;

	void resolve_type(type_ptr& type, ast_ptr resolvee);
};