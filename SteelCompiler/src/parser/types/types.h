#pragma once

#include <string>
#include <memory>
#include <vector>

#include "../parser_utils.h"

enum primitive_size {
	PS_SMALL,
	PS_NORMAL,
	PS_LARGE,
};

enum primitive_type {
	DT_UNKNOWN,

	DT_SMALL,
	DT_INT,
	DT_LARGE,
	DT_FLOAT,
	DT_DOUBLE,
	DT_CHAR,
	DT_WIDECHAR,
	DT_STRING,
	DT_WIDESTRING,
	DT_BYTE,
	DT_BOOL,
	DT_VOID,
};

enum data_type_modifier {
	DTM_NONE = 1 << 0,
	DTM_ARRAY = 1 << 1,
	DTM_POINTER = 1 << 2,
};

enum custom_type_type {
	CT_CLASS,
	CT_STRUCT,
	CT_INTERFACE,
};

class data_type {
public:
	data_type()
		: primitive(DT_UNKNOWN), modifiers(DTM_NONE) {
	}
	data_type(primitive_type primitive)
		: primitive(primitive), modifiers(DTM_NONE) {
	}

	virtual bool operator==(const data_type& other) const {
		if (primitive != other.primitive) {
			return false;
		}
		if (modifiers != other.modifiers) {
			return false;
		}
		return true;
	}
	virtual bool operator!=(const data_type& other) const {
		return !(*this == other);
	}

	virtual bool is_primitive() const {
		return true;
	}
	virtual bool is_indexable() const {
		if (primitive == DT_STRING) {
			return true;
		}
		return false;
	}

	virtual int size_of() const {
		if (is_primitive()) {
			return primitive_size_of(primitive);
		}
	}

	virtual std::string type_name() const {
		return to_string(primitive);
	}

	primitive_type primitive; 
	data_type_modifier modifiers;
};

using type_ptr = std::shared_ptr<data_type>;