#include "parser_utils.h"

#include "types/types.h"
#include "types/custom_types.h"

primitive_type to_primitive(token_type tt) {
    primitive_type dt;
    switch (tt) {
	case TT_SMALL:
		dt = DT_SMALL;
		break;
	case TT_INT:
		dt = DT_INT;
		break;
	case TT_LARGE:
		dt = DT_LARGE;
		break;
	case TT_FLOAT:
		dt = DT_FLOAT;
		break;
	case TT_DOUBLE:
		dt = DT_DOUBLE;
		break;
	case TT_CHAR:
		dt = DT_CHAR;
		break;
	case TT_STRING:
		dt = DT_STRING;
		break;
	case TT_BYTE:
		dt = DT_BYTE;
		break;
	case TT_BOOL:
		dt = DT_BOOL;
		break;
	case TT_VOID:
		dt = DT_VOID;
		break;
	default:
		dt = DT_UNKNOWN;
    }
	return dt;
}
std::shared_ptr<class data_type> to_data_type(token& tk) {
	return to_primitive(tk.type) != DT_UNKNOWN ? std::make_shared<data_type>(to_primitive(tk.type)) : to_data_type(tk.value);
}
type_ptr to_data_type(token_type tt) {
	primitive_type prim = to_primitive(tt);
	if (prim != DT_UNKNOWN) {
		return std::make_shared<data_type>(prim);
	}
	// custom type
	return nullptr;
}
type_ptr to_data_type(primitive_type pt) {
	if (pt != DT_UNKNOWN) {
		return std::make_shared<data_type>(pt);
	}
	return nullptr;
}

std::shared_ptr<class data_type> to_data_type(const std::string& type_name) {
	return std::make_shared<custom_type>(type_name);
}

bool is_numeric(primitive_type primitive) {
	switch (primitive) {
	case DT_SMALL:
	case DT_INT:
	case DT_LARGE:
	case DT_FLOAT:
	case DT_DOUBLE:
		return true;
	default:
		return false;
	}
}

int primitive_size_of(primitive_type primitive) {
	switch (primitive) {
	case DT_SMALL: return 2;
	case DT_INT: return 4;
	case DT_LARGE: return 8;
	case DT_FLOAT: return 4;
	case DT_DOUBLE: return 8;
	case DT_CHAR: return 1;
	case DT_STRING: return 8;
	case DT_BYTE: return 1;
	case DT_BOOL: return 1;
	case DT_VOID: return 0;
	default: return -1;
	}
}

std::string to_string(primitive_type primitive) {
	switch (primitive) {
	case DT_SMALL: return "small";
	case DT_INT: return "int";
	case DT_LARGE: return "large";
	case DT_FLOAT: return "float";
	case DT_DOUBLE: return "double";
	case DT_CHAR: return "char";
	case DT_STRING: return "string";
	case DT_BYTE: return "byte";
	case DT_BOOL: return "bool";
	case DT_VOID: return "void";
	default: return "unknown";
	}
}