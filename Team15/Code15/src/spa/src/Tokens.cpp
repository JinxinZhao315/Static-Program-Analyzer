#pragma once
#include "Tokens.h"

using namespace Tokens;

TokenMap::TokenMap() {
    std::map<std::string , Tokens::Keyword> TOKEN_MAP = {
            {"procedure", Keyword::PROCEDURE},
            {"while", Keyword::WHILE},
            {"if", Keyword::IF},
            {"else", Keyword::ELSE},
            {"(", Keyword::OPEN_BRACKET},
            {")", Keyword::CLOSE_BRACKET, },
            {"{", Keyword::OPEN_CURLY_BRACE},
            {"}", Keyword::CLOSE_CURLY_BRACE},
            {";", Keyword::SEMICOLON},
            {"=", Keyword::ASSIGN},
            {"read", Keyword::READ},
            {"call", Keyword::CALL},
            {"print", Keyword::PRINT},
            {"+", Keyword::ADD},
            {"-", Keyword::SUBTRACT},
            {"*", Keyword::MULTIPLY},
            {"/", Keyword::DIVIDE},
            {"%", Keyword::MODULO},
            {">", Keyword::GT},
            {">=", Keyword::GTE},
            {"<", Keyword::LT},
            {"<=", Keyword::LTE},
            {"==", Keyword::EQUAL},
            {"!=", Keyword::NOT_EQUAL},
            {"!", Keyword::NOT},
            {"&&", Keyword::AND},
            {"||",Keyword::OR}
    };

    std::map<Tokens::Keyword, std::string> STRING_MAP = {
            {Keyword::PROCEDURE, "procedure"},
            {Keyword::WHILE, "while"},
            {Keyword::IF, "if"},
            {Keyword::ELSE, "else"},
            {Keyword::OPEN_BRACKET, "("},
            {Keyword::CLOSE_BRACKET, ")" },
            {Keyword::OPEN_CURLY_BRACE, "{"},
            {Keyword::CLOSE_CURLY_BRACE, "}"},
            {Keyword::SEMICOLON, ";"},
            {Keyword::ASSIGN, "="},
            {Keyword::READ, "read"},
            {Keyword::CALL, "call"},
            {Keyword::PRINT, "print"},
            {Keyword::ADD, "+"},
            {Keyword::SUBTRACT, "-"},
            {Keyword::MULTIPLY, "*"},
            {Keyword::DIVIDE, "/"},
            {Keyword::MODULO, "%"},
            {Keyword::GT, ">"},
            {Keyword::GTE, ">="},
            {Keyword::LT, "<"},
            {Keyword::LTE, "<="},
            {Keyword::EQUAL, "=="},
            {Keyword::NOT_EQUAL, "!="},
            {Keyword::NOT, "!"},
            {Keyword::AND, "&&"},
            {Keyword::OR,"||"}
    };

    TokenMap::setMap(STRING_MAP, TOKEN_MAP);
}

void TokenMap::setMap(std::map<Keyword, std::string> mapToString, std::map<std::string, Keyword> mapToKeyword) {
    TokenMap::doubleKeyedTokenMap = std::make_pair(mapToString, mapToKeyword);
}

std::string TokenMap::getStringByToken(Keyword keyword) {
    return TokenMap::doubleKeyedTokenMap.first.at(keyword);
}

Keyword TokenMap::getTokenByString(std::string token) {
    return TokenMap::doubleKeyedTokenMap.second.at(token);
}
