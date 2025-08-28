#include "core.h"

std::vector<conversion_declaration> get_core_conversions(type_ptr from) {
    static std::vector<conversion_declaration> builtin_conversions = {
        {DT_INT, DT_FLOAT, true},
        {DT_FLOAT, DT_INT, true},
        {DT_INT, DT_CHAR},
        {DT_CHAR, DT_INT},
        {DT_CHAR, DT_STRING},
        {DT_BOOL, DT_INT},
        {DT_INT, DT_BOOL},
    };
    if (!from) {
        return builtin_conversions;
    }
    std::vector<conversion_declaration> filtered_conversions;
    for (const auto& conv : builtin_conversions) {
        if (*conv.from == *from) {
            filtered_conversions.push_back(conv);
        }
    }
    return filtered_conversions;
}
std::vector<operator_declaration> get_core_operators(token_type filter) {
    static std::vector<operator_declaration> builtin_ops = {
        // addition
        {DT_STRING,    DT_STRING,    TT_ADD,        DT_STRING},
        {DT_STRING,    DT_STRING,    TT_ADD,        DT_CHAR},
        {DT_STRING,    DT_CHAR,      TT_ADD,        DT_STRING},
        {DT_CHAR,      DT_CHAR,      TT_ADD,        DT_INT},
        {DT_CHAR,      DT_INT,       TT_ADD,        DT_CHAR},
        {DT_CHAR,      DT_CHAR,      TT_ADD,        DT_CHAR},
        {DT_INT,       DT_INT,       TT_ADD,        DT_INT},
        {DT_FLOAT,     DT_FLOAT,     TT_ADD,        DT_FLOAT},
        {DT_FLOAT,     DT_INT,       TT_ADD,        DT_FLOAT},
        {DT_FLOAT,     DT_FLOAT,     TT_ADD,        DT_INT},
        {DT_INT,       DT_FLOAT,     TT_ADD,        DT_FLOAT},

        // subtraction
        {DT_INT,       DT_INT,       TT_SUBTRACT,   DT_INT},
        {DT_FLOAT,     DT_FLOAT,     TT_SUBTRACT,   DT_FLOAT},
        {DT_FLOAT,     DT_INT,       TT_SUBTRACT,   DT_FLOAT},
        {DT_FLOAT,     DT_FLOAT,     TT_SUBTRACT,   DT_INT},
        {DT_INT,       DT_FLOAT,     TT_SUBTRACT,   DT_FLOAT},
        {DT_CHAR,      DT_CHAR,      TT_SUBTRACT,   DT_CHAR},
        {DT_CHAR,      DT_CHAR,      TT_SUBTRACT,   DT_INT},

        // multiplication
        {DT_STRING,    DT_STRING,    TT_MULTIPLY,   DT_INT},
        {DT_STRING,    DT_CHAR,      TT_MULTIPLY,   DT_INT},
        {DT_STRING,    DT_INT,       TT_MULTIPLY,   DT_STRING},
        {DT_STRING,    DT_INT,       TT_MULTIPLY,   DT_CHAR},
        {DT_STRING,    DT_CHAR,      TT_MULTIPLY,   DT_STRING},
        {DT_CHAR,      DT_INT,       TT_MULTIPLY,   DT_CHAR},
        {DT_INT,       DT_STRING,    TT_MULTIPLY,   DT_STRING},
        {DT_INT,       DT_CHAR,      TT_MULTIPLY,   DT_STRING},
        {DT_INT,       DT_INT,       TT_MULTIPLY,   DT_INT},
        {DT_FLOAT,     DT_FLOAT,     TT_MULTIPLY,   DT_FLOAT},
        {DT_FLOAT,     DT_INT,       TT_MULTIPLY,   DT_FLOAT},
        {DT_FLOAT,     DT_FLOAT,     TT_MULTIPLY,   DT_INT},
        {DT_INT,       DT_FLOAT,     TT_MULTIPLY,   DT_FLOAT},

        // division
        {DT_INT,       DT_INT,       TT_DIVIDE,     DT_INT},
        {DT_FLOAT,     DT_FLOAT,     TT_DIVIDE,     DT_FLOAT},
        {DT_FLOAT,     DT_INT,       TT_DIVIDE,     DT_FLOAT},
        {DT_FLOAT,     DT_FLOAT,     TT_DIVIDE,     DT_INT},
        {DT_INT,       DT_FLOAT,     TT_DIVIDE,     DT_FLOAT},

        // modulo
        {DT_INT,       DT_INT,       TT_MODULO,     DT_INT},
        {DT_FLOAT,     DT_FLOAT,     TT_MODULO,     DT_FLOAT},
        {DT_FLOAT,     DT_INT,       TT_MODULO,     DT_FLOAT},
        {DT_FLOAT,     DT_FLOAT,     TT_MODULO,     DT_INT},
        {DT_INT,       DT_FLOAT,     TT_MODULO,     DT_FLOAT},
        {DT_CHAR,      DT_CHAR,      TT_MODULO,     DT_INT},
        {DT_INT,       DT_INT,       TT_MODULO,     DT_CHAR},

        // comparison
        {DT_BOOL,      DT_INT,       TT_LESS,       DT_INT},
        {DT_BOOL,      DT_INT,       TT_LESS_EQ,    DT_INT},
        {DT_BOOL,      DT_INT,       TT_GREATER,    DT_INT},
        {DT_BOOL,      DT_INT,       TT_GREATER_EQ, DT_INT},
        {DT_BOOL,      DT_FLOAT,     TT_LESS,       DT_FLOAT},
        {DT_BOOL,      DT_FLOAT,     TT_LESS_EQ,    DT_FLOAT},
        {DT_BOOL,      DT_FLOAT,     TT_GREATER,    DT_FLOAT},
        {DT_BOOL,      DT_FLOAT,     TT_GREATER_EQ, DT_FLOAT},

        // logical
        {DT_BOOL,      DT_BOOL,      TT_AND,        DT_BOOL},
        {DT_BOOL,      DT_BOOL,      TT_OR,         DT_BOOL},

        // equality
        {DT_BOOL,      DT_INT,       TT_EQUAL,      DT_INT},
        {DT_BOOL,      DT_INT,       TT_NOT_EQUAL,  DT_INT},
        {DT_BOOL,      DT_FLOAT,     TT_EQUAL,      DT_FLOAT},
        {DT_BOOL,      DT_FLOAT,     TT_NOT_EQUAL,  DT_FLOAT},
        {DT_BOOL,      DT_BOOL,      TT_EQUAL,      DT_BOOL},
        {DT_BOOL,      DT_BOOL,      TT_NOT_EQUAL,  DT_BOOL},
        {DT_BOOL,      DT_CHAR,      TT_EQUAL,      DT_CHAR},
        {DT_BOOL,      DT_CHAR,      TT_NOT_EQUAL,  DT_CHAR},
        {DT_BOOL,      DT_STRING,    TT_EQUAL,      DT_STRING},
        {DT_BOOL,      DT_STRING,    TT_NOT_EQUAL,  DT_STRING},
    };
    if (filter == TT_UNKNOWN) {
        return builtin_ops;
    }
    std::vector<operator_declaration> filtered_ops;
    for (const auto& op : builtin_ops) {
        if (op.oparator == filter) {
            filtered_ops.push_back(op);
        }
    }
    return filtered_ops;
}