#include "common/include/models/Keywords.h"
#include <map>

Keywords::Keywords() {
    auto* keys = new vector<string>();
    *keys = {
            "procedure",
            "variable",
            "stmt", 
            "assign", 
            "constant", 
            "while",
            "if",
            "then",
            "else",
            "{",
            "}",
            "(",
            ")",
            ";",
            "=",
            "read",
            "call",
            "print",
            "+",
            "*",
            "/",
            "-",
            "%",
            ">",
            "<",
            ">=",
            "<=",
            "==",
            "!=",
            "&&",
            "||",
            "!",
            "return",
            "true",
            "false"
    };
    keywordMap = {{
        {"procedure", PROCEDURE },
        {"variable", VARIABLE},
        {"stmt", STMT},
        {"assign", ASSIGN_STMT},
        {"constant", CONSTANT},
        {"while", WHILE},
        {"if", IF },
        {"then", THEN},
        {"else", ELSE},
        {"{", OPEN_CURLY},
        {"}", CLOSE_CURLY},
        {"(", OPEN_PAREN},
        {")", CLOSE_PAREN},
        {";", SEMICOLON},
        {"=", ASSIGN},
        {"read", READ},
        {"call", CALL},
        {"print", PRINT},
        {"+", PLUS},
        {"*", TIMES},
        {"/", DIVIDE},
        {"-", MINUS},
        {"%", MODULO},
        {">", GT},
        {"<", LT},
        {">=", GTE},
        {"<=", LTE},
        {"==", EQUAL},
        {"!=", NOT_EQUAL},
        {"&&", AND},
        {"||", OR},
        {"!", NOT},
        {"return", RETURN},
        {"true", TRUE},
        {"false", FALSE},
        {"", NONE}}, {
        {PROCEDURE, "procedure" },
        {VARIABLE, "variable"},
        {STMT, "stmt"},
        {ASSIGN_STMT, "assign"},
        {CONSTANT, "constant"},
        {WHILE, "while"},
        {IF, "if" },
        {THEN, "then"},
        {ELSE, "else"},
        {OPEN_CURLY, "{"},
        {CLOSE_CURLY, "}"},
        {OPEN_PAREN, "("},
        {CLOSE_PAREN, ")"},
        {SEMICOLON, ";"},
        {ASSIGN, "="},
        {READ, "read"},
        {CALL, "call"},
        {PRINT, "print", },
        {PLUS, "+"},
        {TIMES, "*"},
        {DIVIDE, "/"},
        {MINUS, "-"},
        {MODULO, "%"},
        {GT, ">"},
        {LT, "<"},
        {GTE, ">="},
        {LTE, "<="},
        {EQUAL, "=="},
        {NOT_EQUAL, "!="},
        {AND, "&&"},
        {OR, "||"},
        {NOT, "!"},
        {RETURN, "return"},
        {TRUE, "true"},
        {FALSE, "false"},
        {NONE, ""}}
    };
    keywords = keys;
    sort(keywords->begin(), keywords->end(), [](auto first, auto second) {
        return second.length() < first.length();
    });
}

bool Keywords::isKeyword(string token) {
    for(auto keyword : *keywords) {
        if(keyword == token) {
            return true;
        }
    }
    return false;
}

vector<string>* Keywords::getKeywords() {
    return this->keywords;
}
