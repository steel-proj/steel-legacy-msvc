#include "type_resolver.h"

#include "../../ast/ast.h"
#include "../../parser_utils.h"
#include "../../types/types.h"
#include "../../types/custom_types.h"

void type_resolver::visit(std::shared_ptr<function_decleration> func) {
	// resolve return type
	resolve_type(func->return_type, func);

	// resolve parameter types
	for (auto& param : func->parameters) {
		resolve_type(param->type, param);
	}

	func->body->accept(*this);
}
void type_resolver::visit(std::shared_ptr<constructor_decleration> constructor) {
	// resolve parameter types
	for (auto& param : constructor->parameters) {
		resolve_type(param->type, param);
	}

	constructor->body->accept(*this);
}
void type_resolver::visit(std::shared_ptr<variable_decleration> var) {
	// resolve variable type
	resolve_type(var->type, var);
}
void type_resolver::visit(std::shared_ptr<type_decleration> decl) {
	// resolve member types
	for (auto& member : decl->fields) {
		resolve_type(member->type, member);
	}
	// resolve constructor types
	for (auto& constructor : decl->constructors) {
		constructor->accept(*this);
	}
	// resolve method types
	for (auto& method : decl->methods) {
		method->accept(*this);
	}
	// resolve operator types
	for (auto& op : decl->operators) {
		op->accept(*this);
	}
}
void type_resolver::visit(std::shared_ptr<function_call> func_call) {
	for (auto& arg : func_call->args) {
		arg->accept(*this);
	}
}
void type_resolver::visit(std::shared_ptr<constructor_call> constructor_call) {
	for (auto& arg : constructor_call->args) {
		arg->accept(*this);
	}
}

void type_resolver::resolve_type(type_ptr& type, ast_ptr resolvee) {
	// this function seems to lack any errors
	// the reason is because no custom types will break through
	// that dont exist, as they will be caught as an "unknown identifier"
	// in the parser
	if (auto custom = std::dynamic_pointer_cast<custom_type>(type)) {
		custom->decleration = sym_table->get_type(custom->identifier);
		// (worst case scenario)
		if (!custom->decleration) {
			ERROR(ERR_UNKNOWN_TYPE, resolvee->position, custom->identifier.c_str());
			return;
		}
	}
}