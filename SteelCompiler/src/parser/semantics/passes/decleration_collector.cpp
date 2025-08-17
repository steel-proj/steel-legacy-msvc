#include "decleration_collector.h"

#include "../../ast/ast.h"

void decleration_collector::visit(std::shared_ptr<function_decleration> func) {
	// functions cannot be nested
	if (current_function || current_constructor) {
		ERROR(ERR_NESTED_FUNCTION_NOT_ALLOWED, func->position);
		return;
	}

	// void parameters are not allowed
	for (const auto& param : func->parameters) {
		if (param->type->is_primitive() && param->type->primitive == DT_VOID) {
			ERROR(ERR_PARAM_VOID_TYPE, func->position);
			return;
		}
	}

	// 'Main' cant be overloaded
	if (func->identifier == "Main") {
		if (sym_table->get_function("Main")) {
			ERROR(ERR_MAIN_OVERLOADED, func->position);
			return;
		}
	}

	// if were in a type it must be a method
	if (current_type) {
		func->is_method = true;
	}
	else {
		// check if function is already defined (global)
		int err = sym_table->add_function(func);
		if (err != 0) {
			ERROR((error_code)err, func->position, func->identifier.c_str());
			return;
		}
	}

	current_function = func;
	func->body->accept(*this);
	current_function = nullptr;
}
void decleration_collector::visit(std::shared_ptr<constructor_decleration> constructor) {
	// constructors cannot be nested
	if (current_constructor || current_function) {
		ERROR(ERR_NESTED_CONSTRUCTOR_NOT_ALLOWED, constructor->position);
		return;
	}

	// constructors cannot be defined outside of a type decleration
	if (!current_type) {
		ERROR(ERR_CONSTRUCTOR_OUTSIDE_TYPE, constructor->position);
		return;
	}

	// void parameters are not allowed
	for (const auto& param : constructor->parameters) {
		if (param->type->is_primitive() && param->type->primitive == DT_VOID) {
			ERROR(ERR_PARAM_VOID_TYPE, constructor->position);
			return;
		}
	}

	// check if constructor is already defined
	for (const auto& existing_constructor : current_type->constructors) {
		if (existing_constructor != constructor && existing_constructor->parameters == constructor->parameters) {
			ERROR(ERR_CONSTRUCTOR_OVERLOAD_EXISTS, constructor->position);
			return;
		}
	}

	current_constructor = constructor;
	constructor->body->accept(*this);
	current_constructor = nullptr;
}
void decleration_collector::visit(std::shared_ptr<variable_decleration> var) {
	// NOTE: only global variables should be picked up here
	// local variables will be handled in a later pass

	// no variables should be of type void
	if (var->type->is_primitive() && var->type->primitive == DT_VOID) {
		ERROR(ERR_VARIABLE_VOID_TYPE, var->position);
		return;
	}

	if (!current_function && !current_constructor && !current_type) {
		if (!sym_table->add_variable(var)) {
			ERROR(ERR_VARIABLE_ALREADY_DECLARED, var->position, var->identifier.c_str());
			return;
		}
	}
}
void decleration_collector::visit(std::shared_ptr<type_decleration> decl) {
	// check if type is already defined
	if (!sym_table->add_type(decl)) {
		ERROR(ERR_TYPE_ALREADY_DEFINED, decl->position, decl->type_name().c_str());
		return;
	}

	// types cannot be nested (yet)
	if (current_type) {
		ERROR(ERR_NESTED_TYPE_DECLARATION_NOT_ALLOWED, decl->position);
		return;
	}

	// structs cannot contain methods
	if (decl->type_kind == CT_STRUCT && !decl->methods.empty()) {
		ERROR(ERR_STRUCT_CONTAINS_METHOD, decl->position);
		return;
	}

	// interfaces cannot contain constructors or member variables
	if (decl->type_kind == CT_INTERFACE && !decl->constructors.empty()) {
		ERROR(ERR_INTERFACE_CONTAINS_CONSTRUCTOR, decl->position);
		return;
	}
	if (decl->type_kind == CT_INTERFACE && !decl->fields.empty()) {
		ERROR(ERR_INTERFACE_CONTAINS_MEMBER_VAR, decl->position);
		return;
	}

	current_type = decl;
	for (const auto& member : decl->fields) {
		member->accept(*this);
	}
	for (const auto& constructor : decl->constructors) {
		constructor->accept(*this);
	}
	for (const auto& method : decl->methods) {
		method->accept(*this);
	}
	for (const auto& op : decl->operators) {
		op->accept(*this);
	}
	current_type = nullptr;
}