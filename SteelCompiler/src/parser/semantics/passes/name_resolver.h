#pragma once

#include <string>
#include <map>

#include "../../ast/ast_visitor.h"
#include "../../compilation_pass.h"
#include "../../symbolics/symbol_table.h"

class name_resolver : public ast_visitor, public compilation_pass {
public:
	name_resolver(std::shared_ptr<symbol_table> sym_table)
		: sym_table(sym_table) {
	}

	void visit(std::shared_ptr<class function_decleration> func) override;
	void visit(std::shared_ptr<class constructor_decleration> constructor) override;
	void visit(std::shared_ptr<class variable_decleration> var) override;
	void visit(std::shared_ptr<class type_decleration> decl) override;
	void visit(std::shared_ptr<class binary_expression> expr) override;
	void visit(std::shared_ptr<class identifier_expression> expr) override;
	void visit(std::shared_ptr<class this_expression> expr) override;
	void visit(std::shared_ptr<class member_expression> expr) override;
	void visit(std::shared_ptr<class function_call> func_call) override;
	void visit(std::shared_ptr<class constructor_call> constructor_call) override;
	void visit(std::shared_ptr<class block_statement> block) override;
	void visit(std::shared_ptr<class if_statement> if_stmt) override;
	void visit(std::shared_ptr<class for_loop> for_loop) override;
	void visit(std::shared_ptr<class while_loop> while_loop) override;

private:
	std::shared_ptr<symbol_table> sym_table;

	std::shared_ptr<class function_decleration> current_func;
	std::shared_ptr<class constructor_decleration> current_ctor;
	std::shared_ptr<class type_decleration> current_type;
};