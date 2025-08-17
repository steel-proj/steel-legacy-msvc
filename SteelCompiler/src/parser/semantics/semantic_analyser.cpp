#include "semantic_analyser.h"

#include <iostream>

#include "passes/decleration_collector.h"
#include "passes/type_resolver.h"
#include "passes/name_resolver.h"
#include "passes/type_checker.h"
#include "passes/init_checker.h"
#include "passes/flow_analyzer.h"

void semantic_analyser::analyse() {
	decleration_collector dec_collector(sym_table);
	program->accept(dec_collector);
	for (const auto& error : dec_collector.get_errors()) {
		errors.push_back(error);
	}

	type_resolver type_resolver(sym_table);
	program->accept(type_resolver);
	for (const auto& error : type_resolver.get_errors()) {
		errors.push_back(error);
	}

	name_resolver name_resolver(sym_table);
	program->accept(name_resolver);
	for (const auto& error : name_resolver.get_errors()) {
		errors.push_back(error);
	}

	type_checker type_checker(sym_table);
	program->accept(type_checker);
	for (const auto& error : type_checker.get_errors()) {
		errors.push_back(error);
	}

	init_checker init_checker(sym_table);
	program->accept(init_checker);
	for (const auto& error : init_checker.get_errors()) {
		errors.push_back(error);
	}

	flow_analyzer flow_analyzer(sym_table);
	program->accept(flow_analyzer);
	for (const auto& error : flow_analyzer.get_errors()) {
		errors.push_back(error);
	}
}