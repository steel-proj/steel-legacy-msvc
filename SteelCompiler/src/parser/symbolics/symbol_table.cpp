#include "symbol_table.h"

#include "../../error/error_catalog.h"

symbol_table::symbol_table() {
	scopes.emplace_back(); // global scope
}

void symbol_table::push_scope() {
	scopes.emplace_back();
}
void symbol_table::pop_scope() {
	if (!scopes.empty()) {
		scopes.pop_back();
	}
}

std::vector<operator_decleration> symbol_table::get_builtin_operators(token_type filter) {
    static std::vector<operator_decleration> builtin_ops = {
        // addition
        {DT_STRING,    DT_STRING,    TT_ADD,        DT_STRING},
        {DT_STRING,    DT_STRING,    TT_ADD,        DT_CHAR},
        {DT_STRING,    DT_CHAR,      TT_ADD,        DT_STRING},
        {DT_CHAR,      DT_CHAR,      TT_ADD,        DT_INT},
        {DT_CHAR,      DT_INT,       TT_ADD,        DT_CHAR},
        {DT_CHAR,      DT_CHAR,      TT_ADD,        DT_CHAR},
        {DT_INT,       DT_INT,       TT_ADD,        DT_INT},
        {DT_FLOAT,     DT_FLOAT,     TT_ADD,        DT_FLOAT},
        {DT_FLOAT,     DT_INT,       TT_ADD,        DT_FLOAT},
        {DT_FLOAT,     DT_FLOAT,     TT_ADD,        DT_INT},
        {DT_INT,       DT_FLOAT,     TT_ADD,        DT_FLOAT},

        // subtraction
        {DT_INT,       DT_INT,       TT_SUBTRACT,   DT_INT},
        {DT_FLOAT,     DT_FLOAT,     TT_SUBTRACT,   DT_FLOAT},
        {DT_FLOAT,     DT_INT,       TT_SUBTRACT,   DT_FLOAT},
        {DT_FLOAT,     DT_FLOAT,     TT_SUBTRACT,   DT_INT},
        {DT_INT,       DT_FLOAT,     TT_SUBTRACT,   DT_FLOAT},
        {DT_CHAR,      DT_CHAR,      TT_SUBTRACT,   DT_CHAR},
        {DT_CHAR,      DT_CHAR,      TT_SUBTRACT,   DT_INT},

        // multiplication
        {DT_STRING,    DT_STRING,    TT_MULTIPLY,   DT_INT},
        {DT_STRING,    DT_CHAR,      TT_MULTIPLY,   DT_INT},
        {DT_STRING,    DT_INT,       TT_MULTIPLY,   DT_STRING},
        {DT_STRING,    DT_INT,       TT_MULTIPLY,   DT_CHAR},
        {DT_STRING,    DT_CHAR,      TT_MULTIPLY,   DT_STRING},
        {DT_CHAR,      DT_INT,       TT_MULTIPLY,   DT_CHAR},
        {DT_INT,       DT_STRING,    TT_MULTIPLY,   DT_STRING},
        {DT_INT,       DT_CHAR,      TT_MULTIPLY,   DT_STRING},
        {DT_INT,       DT_INT,       TT_MULTIPLY,   DT_INT},
        {DT_FLOAT,     DT_FLOAT,     TT_MULTIPLY,   DT_FLOAT},
        {DT_FLOAT,     DT_INT,       TT_MULTIPLY,   DT_FLOAT},
        {DT_FLOAT,     DT_FLOAT,     TT_MULTIPLY,   DT_INT},
        {DT_INT,       DT_FLOAT,     TT_MULTIPLY,   DT_FLOAT},

        // division
        {DT_INT,       DT_INT,       TT_DIVIDE,     DT_INT},
        {DT_FLOAT,     DT_FLOAT,     TT_DIVIDE,     DT_FLOAT},
        {DT_FLOAT,     DT_INT,       TT_DIVIDE,     DT_FLOAT},
        {DT_FLOAT,     DT_FLOAT,     TT_DIVIDE,     DT_INT},
        {DT_INT,       DT_FLOAT,     TT_DIVIDE,     DT_FLOAT},

        // modulo
        {DT_INT,       DT_INT,       TT_MODULO,     DT_INT},
        {DT_FLOAT,     DT_FLOAT,     TT_MODULO,     DT_FLOAT},
        {DT_FLOAT,     DT_INT,       TT_MODULO,     DT_FLOAT},
        {DT_FLOAT,     DT_FLOAT,     TT_MODULO,     DT_INT},
        {DT_INT,       DT_FLOAT,     TT_MODULO,     DT_FLOAT},
        {DT_CHAR,      DT_CHAR,      TT_MODULO,     DT_INT},
        {DT_INT,       DT_INT,       TT_MODULO,     DT_CHAR},

        // comparison
        {DT_BOOL,      DT_INT,       TT_LESS,       DT_INT},
        {DT_BOOL,      DT_INT,       TT_LESS_EQ,    DT_INT},
        {DT_BOOL,      DT_INT,       TT_GREATER,    DT_INT},
        {DT_BOOL,      DT_INT,       TT_GREATER_EQ, DT_INT},
        {DT_BOOL,      DT_FLOAT,     TT_LESS,       DT_FLOAT},
        {DT_BOOL,      DT_FLOAT,     TT_LESS_EQ,    DT_FLOAT},
        {DT_BOOL,      DT_FLOAT,     TT_GREATER,    DT_FLOAT},
        {DT_BOOL,      DT_FLOAT,     TT_GREATER_EQ, DT_FLOAT},

        // logical
        {DT_BOOL,      DT_BOOL,      TT_AND,        DT_BOOL},
        {DT_BOOL,      DT_BOOL,      TT_OR,         DT_BOOL},

        // equality
        {DT_BOOL,      DT_INT,       TT_EQUAL,      DT_INT},
        {DT_BOOL,      DT_INT,       TT_NOT_EQUAL,  DT_INT},
        {DT_BOOL,      DT_FLOAT,     TT_EQUAL,      DT_FLOAT},
        {DT_BOOL,      DT_FLOAT,     TT_NOT_EQUAL,  DT_FLOAT},
        {DT_BOOL,      DT_BOOL,      TT_EQUAL,      DT_BOOL},
        {DT_BOOL,      DT_BOOL,      TT_NOT_EQUAL,  DT_BOOL},
        {DT_BOOL,      DT_CHAR,      TT_EQUAL,      DT_CHAR},
        {DT_BOOL,      DT_CHAR,      TT_NOT_EQUAL,  DT_CHAR},
        {DT_BOOL,      DT_STRING,    TT_EQUAL,      DT_STRING},
        {DT_BOOL,      DT_STRING,    TT_NOT_EQUAL,  DT_STRING},
    };
    if (filter == TT_UNKNOWN) {
		return builtin_ops;
    }
	std::vector<operator_decleration> filtered_ops;
	for (const auto& op : builtin_ops) {
		if (op.oparator == filter) {
			filtered_ops.push_back(op);
		}
	}
	return filtered_ops;
}

std::vector<conversion_decleration> symbol_table::get_builtin_conversions(type_ptr from) {
	static std::vector<conversion_decleration> builtin_conversions = {
		{DT_INT, DT_FLOAT, true},
		{DT_FLOAT, DT_INT, true},
		{DT_INT, DT_CHAR},
		{DT_CHAR, DT_INT},
		{DT_CHAR, DT_STRING},
		{DT_BOOL, DT_INT},
		{DT_INT, DT_BOOL},
	};
	if (!from) {
		return builtin_conversions;
	}
	std::vector<conversion_decleration> filtered_conversions;
	for (const auto& conv : builtin_conversions) {
		if (*conv.from == *from) {
			filtered_conversions.push_back(conv);
		}
	}
	return filtered_conversions;
}

bool symbol_table::add_variable(std::shared_ptr<variable_decleration> var) {
	auto& current_scope = scopes.back();
	if (current_scope.find(var->identifier) != current_scope.end()) {
		return false;
	}
    current_scope[var->identifier] = var;
	return true;
}
bool symbol_table::add_field(std::shared_ptr<type_decleration> type, std::shared_ptr<variable_decleration> var) {
    for (auto& field : type->fields) {
        if (field->identifier == var->identifier) {
            return false; // field already exists
        }
    }
	type->fields.push_back(var);
	return true;
}
int symbol_table::add_function(std::shared_ptr<function_decleration> func) {
    for (const auto& existing : functions) {
        const auto& existing_func = existing.second;
        if (existing.first == func->identifier) {
            // check params match
            if (existing_func->parameters.size() == func->parameters.size()) {
                bool params_match = true;
                for (size_t i = 0; i < func->parameters.size(); ++i) {
                    if (*existing_func->parameters[i]->type != *func->parameters[i]->type) {
                        params_match = false;
                        break;
                    }
                }
                if (params_match) {
                    // already defined
                    return ERR_FUNC_ALREADY_DEFINED;
                }
            }

            if (*existing_func->return_type != *func->return_type) {
                return ERR_RETURN_TYPE_CANT_OVERLOAD; // cannot overload by return type
            }
        }
    }
    functions.emplace_back(func->identifier, func);
    return 0;
}
int symbol_table::add_method(std::shared_ptr<type_decleration> type, std::shared_ptr<function_decleration> func) {
	// check if method already exists in type
	for (const auto& method : type->methods) {
		if (method->identifier == func->identifier) {
			// check params match
			if (method->parameters.size() == func->parameters.size()) {
				bool params_match = true;
				for (size_t i = 0; i < func->parameters.size(); ++i) {
					if (*method->parameters[i]->type != *func->parameters[i]->type) {
						params_match = false;
						break;
					}
				}
				if (params_match) {
					return ERR_FUNC_ALREADY_DEFINED; // already defined
				}
			}
			if (*method->return_type != *func->return_type) {
				return ERR_RETURN_TYPE_CANT_OVERLOAD; // cannot overload by return type
			}
		}
	}
    type->methods.push_back(func);
    return true;
}
bool symbol_table::add_type(std::shared_ptr<type_decleration> type) {
	if (types.find(type->type_name()) != types.end()) {
		return false;
	}
	types[type->type_name()] = type;
	return true;
}

std::shared_ptr<variable_decleration> symbol_table::get_variable(const std::string& name) const {
	for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
		auto found = it->find(name);
        if (found != it->end()) {
            return found->second;
        }
	}
	return nullptr;
}
std::shared_ptr<variable_decleration> symbol_table::get_variable(std::shared_ptr<type_decleration> type, const std::string& name) const {
    // search through fields first
    if (type != nullptr) {
        for (auto& field : type->fields) {
            if (field->identifier == name) {
                return field;
            }
        }
    }
    // search globally
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            return found->second;
        }
    }
    return nullptr;
}
std::shared_ptr<function_decleration> symbol_table::get_function(const std::string& name) const {
	for (const auto& func : functions) {
		if (func.first == name) {
			return func.second;
		}
	}
	return nullptr;
}
std::shared_ptr<function_decleration> symbol_table::get_function(const std::string& name, type_ptr return_type) const {
	for (const auto& func : functions) {
		if (func.first == name && *func.second->return_type == *return_type) {
			return func.second;
		}
	}
	return nullptr;
}
std::shared_ptr<function_decleration> symbol_table::get_function(const std::string& name, type_ptr return_type, std::vector<type_ptr> param_types) const {
	for (const auto& func : functions) {
		if (func.first == name && *func.second->return_type == *return_type) {
            for (size_t i = 0; i < func.second->parameters.size(); ++i) {
                if (i < param_types.size() && *func.second->parameters[i]->type == *param_types[i]) {
			        return func.second;
                }
            }
		}
	}
	return nullptr;
}
std::shared_ptr<function_decleration> symbol_table::get_function(const std::string& name, std::vector<type_ptr> param_types) const {
    for (const auto& func : functions) {
        if (func.first == name) {
            for (size_t i = 0; i < func.second->parameters.size(); ++i) {
                if (i < param_types.size() && *func.second->parameters[i]->type == *param_types[i]) {
                    return func.second;
                }
            }
        }
    }
    return nullptr;
}
std::vector<std::shared_ptr<function_decleration>> symbol_table::get_function_candidates(const std::string& name, size_t arity) const {
	std::vector<std::shared_ptr<function_decleration>> candidates;
	for (const auto& func : functions) {
		if (func.first == name && func.second->parameters.size() == arity) {
			candidates.push_back(func.second);
		}
	}
	return candidates;
}
std::shared_ptr<function_decleration> symbol_table::get_method(std::shared_ptr<const type_decleration> type, const std::string& name) const {
	if (type != nullptr) {
		for (const auto& method : type->methods) {
			if (method->identifier == name) {
				return method;
			}
		}
	}
	return nullptr;
}
std::shared_ptr<function_decleration> symbol_table::get_method(std::shared_ptr<const type_decleration> type, const std::string& name, type_ptr return_type) const {
	if (type != nullptr) {
		for (const auto& method : type->methods) {
			if (method->identifier == name && *method->return_type == *return_type) {
				return method;
			}
		}
	}
	return nullptr;
}
std::shared_ptr<function_decleration> symbol_table::get_method(std::shared_ptr<const type_decleration> type, const std::string& name, type_ptr return_type, std::vector<type_ptr> param_types) const {
	if (type != nullptr) {
		for (const auto& method : type->methods) {
			if (method->identifier == name && *method->return_type == *return_type) {
				if (method->parameters.size() == param_types.size()) {
					bool params_match = true;
					for (size_t i = 0; i < method->parameters.size(); ++i) {
						if (*method->parameters[i]->type != *param_types[i]) {
							params_match = false;
							break;
						}
					}
					if (params_match) {
						return method;
					}
				}
			}
		}
	}
	return nullptr;
}
std::shared_ptr<function_decleration> symbol_table::get_method(std::shared_ptr<const type_decleration> type, const std::string& name, std::vector<type_ptr> param_types) const {
	if (type != nullptr) {
		for (const auto& method : type->methods) {
			if (method->identifier == name) {
				if (method->parameters.size() == param_types.size()) {
					bool params_match = true;
					for (size_t i = 0; i < method->parameters.size(); ++i) {
						if (*method->parameters[i]->type != *param_types[i]) {
							params_match = false;
							break;
						}
					}
					if (params_match) {
						return method;
					}
				}
			}
		}
	}
	return nullptr;
}
std::vector<std::shared_ptr<function_decleration>> symbol_table::get_method_candidates(std::shared_ptr<const type_decleration> type, const std::string& name, size_t arity) const {
	std::vector<std::shared_ptr<function_decleration>> candidates;
	if (type != nullptr) {
		for (const auto& method : type->methods) {
			if (method->identifier == name && method->parameters.size() == arity) {
				candidates.push_back(method);
			}
		}
	}
	return candidates;
}
std::shared_ptr<type_decleration> symbol_table::get_type(const std::string& name) const {
	auto it = types.find(name);
	if (it != types.end()) {
		return it->second;
	}
	return nullptr;
}