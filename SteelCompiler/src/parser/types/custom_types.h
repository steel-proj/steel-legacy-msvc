#pragma once

#include "types.h"

class type_decleration;

class custom_type : public data_type {
public:
	custom_type(std::shared_ptr<const type_decleration> decleration, std::string identifier)
		: decleration(decleration), identifier(identifier) {
	}
	custom_type(std::string identifier)
		: decleration(nullptr), identifier(identifier) {
		// this is used for types that we know exist but
		// are not at the stage where the decleration is matched
	}

	bool operator==(const data_type& other) const override {
		if (auto custom = dynamic_cast<const custom_type*>(&other)) {
			// easy check - no data types are allowed to have the same identifier
			return identifier == custom->identifier;
		}
		return false;
	}
	bool operator!=(const data_type& other) const {
		return !(*this == other);
	}

	int size_of() const override;

	bool is_primitive() const override {
		return false;
	}
	bool is_indexable() const override {
		return false;
	}

	std::string type_name() const override {
		return identifier;
	}

	std::shared_ptr<const type_decleration> decleration;
	std::string identifier;
};