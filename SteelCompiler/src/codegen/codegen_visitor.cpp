#include "codegen_visitor.h"

void codegen_visitor::add_instruction(std::string opc) {
	pseudo += opc + "\n";
}
void codegen_visitor::add_label(std::string lbl) {
	pseudo += lbl + ":\n";
}