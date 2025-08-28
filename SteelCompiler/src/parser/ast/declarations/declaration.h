#pragma once

#include <string>

#include "../ast_node.h"
#include "../../modifiers/modifiers.h"

class declaration : public ast_node {
public:
	modifiers mods = MOD_NONE;
	std::string filename;
};