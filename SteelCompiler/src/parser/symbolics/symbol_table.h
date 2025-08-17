#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include <utility>

#include "../ast/ast.h"

class symbol_table {
public:
	symbol_table();

	inline bool in_global_scope() const {
		return scopes.size() == 1;
	}
	void push_scope();
	void pop_scope();

	bool add_variable(std::shared_ptr<variable_decleration> var);
	bool add_field(std::shared_ptr<type_decleration> type, std::shared_ptr<variable_decleration> var);
	int add_function(std::shared_ptr<function_decleration> func);
	int add_method(std::shared_ptr<type_decleration> type, std::shared_ptr<function_decleration> func);
	bool add_type(std::shared_ptr<type_decleration> type);

	std::vector<operator_decleration> get_builtin_operators(token_type filter = TT_UNKNOWN);
	std::vector<conversion_decleration> get_builtin_conversions(type_ptr from = nullptr);

	inline bool has_variable(const std::string& name) const {
		return get_variable(name) != nullptr;
	}
	inline bool has_type(const std::string& name) const {
		return types.find(name) != types.end();
	}

	std::shared_ptr<variable_decleration> get_variable(const std::string& name) const;
	std::shared_ptr<variable_decleration> get_variable(std::shared_ptr<type_decleration> type, const std::string& name) const;
	std::shared_ptr<function_decleration> get_function(const std::string& name) const;
	std::shared_ptr<function_decleration> get_function(const std::string& name, type_ptr return_type) const;
	std::shared_ptr<function_decleration> get_function(const std::string& name, type_ptr return_type, std::vector<type_ptr> param_types) const;
	std::shared_ptr<function_decleration> get_function(const std::string& name, std::vector<type_ptr> param_types) const;
	std::vector<std::shared_ptr<function_decleration>> get_function_candidates(const std::string& name, size_t arity) const;
	std::shared_ptr<function_decleration> get_method(std::shared_ptr<const type_decleration> type, const std::string& name) const;
	std::shared_ptr<function_decleration> get_method(std::shared_ptr<const type_decleration> type, const std::string& name, type_ptr return_type) const;
	std::shared_ptr<function_decleration> get_method(std::shared_ptr<const type_decleration> type, const std::string& name, type_ptr return_type, std::vector<type_ptr> param_types) const;
	std::shared_ptr<function_decleration> get_method(std::shared_ptr<const type_decleration> type, const std::string& name, std::vector<type_ptr> param_types) const;
	std::vector<std::shared_ptr<function_decleration>> get_method_candidates(std::shared_ptr<const type_decleration> type, const std::string& name, size_t arity) const;
	std::shared_ptr<type_decleration> get_type(const std::string& name) const;

private:
	std::vector<std::map<std::string, std::shared_ptr<variable_decleration>>> scopes;
	std::vector<std::pair<std::string, std::shared_ptr<function_decleration>>> functions;
	std::unordered_map<std::string, std::shared_ptr<type_decleration>> types;
};