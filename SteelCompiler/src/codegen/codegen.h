#pragma once

#include <memory>

#include "../parser/ast/ast.h"

class codegen {
public:
	codegen(std::shared_ptr<program> program)
		: program(program) {
	}

	std::vector<unsigned char> generate();
	std::string generate_pseudo();

private:
	std::shared_ptr<program> program;
};