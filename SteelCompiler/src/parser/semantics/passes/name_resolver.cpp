#include "name_resolver.h"

#include "../../ast/ast.h"
#include "../../types/custom_types.h"

void name_resolver::visit(std::shared_ptr<function_decleration> func) {
	sym_table->push_scope();
	current_func = func;
	// add parameters to the current scope
	for (const auto& param : func->parameters) {
		if (sym_table->has_variable(param->identifier)) {
			ERROR(ERR_DUPLICATE_PARAMETER, func->position, param->identifier.c_str());
			continue;
		}
		sym_table->add_variable(param);
	}
	func->body->accept(*this);
	current_func = nullptr;
	sym_table->pop_scope();
}
void name_resolver::visit(std::shared_ptr<constructor_decleration> constructor) {
	sym_table->push_scope();
	current_ctor = constructor;
	// add parameters to the current scope
	for (const auto& param : constructor->parameters) {
		if (sym_table->has_variable(param->identifier)) {
			ERROR(ERR_DUPLICATE_PARAMETER, constructor->position, param->identifier.c_str());
			continue;
		}
		sym_table->add_variable(param);
	}
	constructor->body->accept(*this);
	current_ctor = nullptr;
	sym_table->pop_scope();
}
void name_resolver::visit(std::shared_ptr<variable_decleration> var) {
	// only check local variables here - globals are already handled
	// in the decleration collector pass
	if (!sym_table->in_global_scope()) {
		if (!sym_table->add_variable(var)) {
			ERROR(ERR_VARIABLE_ALREADY_DECLARED, var->position, var->identifier.c_str());
			return;
		}
	}
	// still accept all initializers including global ones
	if (var->initializer) {
		var->initializer->accept(*this);
	}
}
void name_resolver::visit(std::shared_ptr<type_decleration> decl) {
	sym_table->push_scope();
	current_type = decl;
	for (const auto& constructor : decl->constructors) {
		constructor->accept(*this);
	}
	for (const auto& member : decl->fields) {
		member->accept(*this);
	}
	for (const auto& method : decl->methods) {
		method->accept(*this);
	}
	for (const auto& op : decl->operators) {
		op->accept(*this);
	}
	current_type = nullptr;
	sym_table->pop_scope();
}
void name_resolver::visit(std::shared_ptr<binary_expression> expr) {
	expr->left->accept(*this);
	expr->right->accept(*this);
}
void name_resolver::visit(std::shared_ptr<identifier_expression> expr) {
	auto var_decl = sym_table->get_variable(current_type, expr->identifier);
	if (!var_decl) {
		ERROR(ERR_UNKNOWN_IDENTIFIER, expr->position, expr->identifier.c_str());
		return;
	}
	expr->decleration = var_decl;
}
void name_resolver::visit(std::shared_ptr<this_expression> expr) {
	if (!current_type && !current_func && !current_ctor) {
		ERROR(ERR_THIS_OUTSIDE_NONSTATIC_METHOD, expr->position);
		return;
	}
	expr->parent_type = current_type->type();
}
void name_resolver::visit(std::shared_ptr<member_expression> expr) {
	expr->object->accept(*this);
	auto type = expr->object->type();
	auto custom = std::dynamic_pointer_cast<custom_type>(type);
	if (!custom || !custom->decleration) {
		ERROR(ERR_MEMBER_ACCESS_ON_NONCOMPOSITE, expr->position, type->type_name().c_str());
		return;
	}

	bool found = false;
	for (const auto& member : custom->decleration->fields) {
		if (member->identifier == expr->member) {
			expr->decleration = member;
			found = true;
			break;
		}
	}
	if (!found) {
		ERROR(ERR_NO_MEMBER_WITH_NAME, expr->position, custom->type_name().c_str(), expr->member.c_str());
		return;
	}
}
void name_resolver::visit(std::shared_ptr<function_call> func_call) {
	if (func_call->is_method()) {
		if (auto member = std::dynamic_pointer_cast<member_expression>(func_call->callee)) {
			// resolve the object
			member->object->accept(*this);

			auto type = member->object->type();
			auto custom = std::dynamic_pointer_cast<custom_type>(type);
			if (!custom || !custom->decleration) {
				ERROR(ERR_MEMBER_ACCESS_ON_NONCOMPOSITE, func_call->position, type->type_name().c_str());
				return;
			}

			// find method - dont check for return type as its unknown in a call
			auto method_candidates = sym_table->get_method_candidates(custom->decleration, func_call->identifier, func_call->args.size());
			if (method_candidates.empty()) {
				ERROR(ERR_NO_MATCHING_METHOD, func_call->position, member->member.c_str());
				return;
			}
			func_call->decleration_candidates = method_candidates;
		}
	}
	else {
		// lookup global function - dont check for return type as its unknown in a call
		auto func_candidates = sym_table->get_function_candidates(func_call->identifier, func_call->args.size());
		if (func_candidates.empty()) {
			ERROR(ERR_UNKNOWN_FUNCTION, func_call->position, func_call->identifier.c_str());
			return;
		}
		func_call->decleration_candidates = func_candidates;
	}

	// resolve args as normal
	for (auto& arg : func_call->args) {
		arg->accept(*this);
	}
}
void name_resolver::visit(std::shared_ptr<constructor_call> constructor_call) {
	auto type_decl = sym_table->get_type(constructor_call->type_name);
	if (!type_decl) {
		ERROR(ERR_UNKNOWN_TYPE, constructor_call->position, constructor_call->type_name.c_str());
		return;
	}
	constructor_call->type_decl = type_decl;
	for (auto& arg : constructor_call->args) {
		arg->accept(*this);
	}
}
void name_resolver::visit(std::shared_ptr<block_statement> block) {
	sym_table->push_scope();
	for (const auto& stmt : block->body) {
		stmt->accept(*this);
	}
	sym_table->pop_scope();
}
void name_resolver::visit(std::shared_ptr<if_statement> if_stmt) {
	// may change this later to support inline variable if statements
	if_stmt->condition->accept(*this);
	//sym_table->push_scope();
	if_stmt->then_block->accept(*this);
	//sym_table->pop_scope();
	if (if_stmt->else_block) {
		if_stmt->else_block->accept(*this);
	}
}
void name_resolver::visit(std::shared_ptr<for_loop> for_loop) {
	sym_table->push_scope();
	if (for_loop->initializer) {
		for_loop->initializer->accept(*this);
	}
	if (for_loop->condition) {
		for_loop->condition->accept(*this);
	}
	if (for_loop->increment) {
		for_loop->increment->accept(*this);
	}
	for_loop->body->accept(*this);
	sym_table->pop_scope();
}
void name_resolver::visit(std::shared_ptr<while_loop> while_loop) {
	if (while_loop->condition) {
		while_loop->condition->accept(*this);
	}
	sym_table->push_scope();
	while_loop->body->accept(*this);
	sym_table->pop_scope();
}