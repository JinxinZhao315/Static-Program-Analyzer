#pragma once

#include <map>
#include <string>

namespace Tokens {
    enum Keyword {
        PROCEDURE,
        WHILE,
        IF,
        ELSE,
        OPEN_BRACKET,
        CLOSE_BRACKET,
        OPEN_CURLY_BRACE,
        CLOSE_CURLY_BRACE,
        SEMICOLON,
        ASSIGN,
        READ,
        CALL,
        PRINT,
        ADD,
        MULTIPLY,
        DIVIDE,
        SUBTRACT,
        MODULO,
        GT,
        GTE,
        LT,
        LTE,
        EQUAL,
        NOT_EQUAL,
        AND,
        OR,
        NOT
    };

    inline static const std::map<std::string , Tokens::Keyword> TOKEN_MAP = {
            {"procedure", Keyword::PROCEDURE},
            {"while", Keyword::WHILE},
            {"if", Keyword::IF},
            {"else", Keyword::ELSE},
            {"(", Keyword::OPEN_BRACKET},
            {")", Keyword::CLOSE_BRACKET, },
            {"{", Keyword::OPEN_CURLY_BRACE},
            {"}", Keyword::CLOSE_CURLY_BRACE},
            {";", Keyword::SEMICOLON},
            {"assign", Keyword::ASSIGN},
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
}
