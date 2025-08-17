#include "codegen.h"

#include "codegen_visitor.h"

std::vector<unsigned char> codegen::generate() {
    std::vector<unsigned char> bytecode;
    return bytecode;
}
std::string codegen::generate_pseudo() {
    codegen_visitor visitor;
    program->accept(visitor);
    return visitor.get_pseudo();
}