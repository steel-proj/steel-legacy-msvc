#pragma once

#include <string>
#include <memory>
#include <vector>

#include "ast_node.h"

class program : public ast_node, public std::enable_shared_from_this<program> {
public:
	ENABLE_ACCEPT(program)

	std::string string(int indent = 0) const override {
		std::string ind = indent_s(indent);
		std::string result = ind + "Program:\n";
		if (declerations.size() <= 0) {
			result += ind + "  <Empty>\n";
			return result;
		}
		for (int i = 0; i < declerations.size(); i++) {
			result += ind + declerations[i]->string(indent + 1) + "\n";
		}
		return result;
	}

	std::vector<ast_ptr> declerations;
};