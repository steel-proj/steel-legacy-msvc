#pragma once

#include <map>
#include <string>
#include <memory>

class ast_visitor {
public:
	virtual void visit(std::shared_ptr<class program> program);
	virtual void visit(std::shared_ptr<class function_decleration> func);
	virtual void visit(std::shared_ptr<class constructor_decleration> constructor);
	virtual void visit(std::shared_ptr<class variable_decleration> var);
	virtual void visit(std::shared_ptr<class type_decleration> decl);
	virtual void visit(std::shared_ptr<class module_decleration> mod);
	virtual void visit(std::shared_ptr<class conversion_decleration> conv);
	virtual void visit(std::shared_ptr<class operator_decleration> op);
	virtual void visit(std::shared_ptr<class expression_statement> expr);
	virtual void visit(std::shared_ptr<class binary_expression> expr);
	virtual void visit(std::shared_ptr<class assignment_expression> expr);
	virtual void visit(std::shared_ptr<class member_expression> expr);
	virtual void visit(std::shared_ptr<class unary_expression> expr);
	virtual void visit(std::shared_ptr<class index_expression> expr);
	virtual void visit(std::shared_ptr<class identifier_expression> expr);
	virtual void visit(std::shared_ptr<class this_expression> expr);
	virtual void visit(std::shared_ptr<class cast_expression> expr);
	virtual void visit(std::shared_ptr<class initializer_list> init);
	virtual void visit(std::shared_ptr<class function_call> func_call);
	virtual void visit(std::shared_ptr<class constructor_call> constructor_call);
	virtual void visit(std::shared_ptr<class literal> literal);
	virtual void visit(std::shared_ptr<class block_statement> block);
	virtual void visit(std::shared_ptr<class if_statement> if_stmt);
	virtual void visit(std::shared_ptr<class for_loop> for_loop);
	virtual void visit(std::shared_ptr<class while_loop> while_loop);
	virtual void visit(std::shared_ptr<class return_statement> ret_stmt);
};