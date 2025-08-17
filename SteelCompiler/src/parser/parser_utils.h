#pragma once

#include <string>
#include <memory>

#include "../lexer/token.h"
#include "../lexer/token_type.h"

enum primitive_type to_primitive(token_type tt);
std::shared_ptr<class data_type> to_data_type(token& tk);
std::shared_ptr<class data_type> to_data_type(token_type tt);
std::shared_ptr<class data_type> to_data_type(primitive_type pt);
std::shared_ptr<class data_type> to_data_type(const std::string& type_name);

bool is_numeric(enum primitive_type primitive);

int primitive_size_of(enum primitive_type primitive);

std::string to_string(enum primitive_type primitive);