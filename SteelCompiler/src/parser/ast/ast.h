#pragma once

#include "program.h"
#include "declerations/function_decleration.h"
#include "declerations/constructor_decleration.h"
#include "declerations/variable_decleration.h"
#include "declerations/type_decleration.h"
#include "declerations/module_decleration.h"
#include "declerations/conversion_decleration.h"
#include "declerations/operator_decleration.h"
#include "statements/block_statement.h"
#include "statements/control_flow/return_statement.h"
#include "statements/control_flow/if_statement.h"
#include "statements/control_flow/for_loop.h"
#include "statements/control_flow/while_loop.h"
#include "expressions/expression.h"
#include "expressions/expression_statement.h"
#include "expressions/binary_expression.h"
#include "expressions/assignment_expression.h"
#include "expressions/member_expression.h"
#include "expressions/unary_expression.h"
#include "expressions/index_expression.h"
#include "expressions/identifier_expression.h"
#include "expressions/this_expression.h"
#include "expressions/cast_expression.h"
#include "expressions/initializer_list.h"
#include "expressions/function_call.h"
#include "expressions/constructor_call.h"
#include "expressions/literal.h"

template<typename T, typename... Args>
inline std::shared_ptr<T> make_ast(token& ast_token, Args... args) {
	static_assert(std::is_base_of<ast_node, T>::value, "T must derive from ast_node");
	std::shared_ptr<T> node = std::make_shared<T>(std::forward<Args>(args)...);
	node->position = ast_token.pos;
	return node;
}
template<typename T, typename ...Args>
inline std::shared_ptr<T> make_ast(Args... args) {
	static_assert(std::is_base_of<ast_node, T>::value, "T must derive from ast_node");
	std::shared_ptr<T> node = std::make_shared<T>(std::forward<Args>(args)...);
	node->position = { 0, 0 };
	return node;
}