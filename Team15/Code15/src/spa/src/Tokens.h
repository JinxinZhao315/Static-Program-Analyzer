#include <map>
#include <string>

namespace Tokens {
    enum class Keyword {
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

    std::map<Keyword, std::string> TOKEN_MAP = {
            {Keyword::PROCEDURE, "procedure"},
            {Keyword::WHILE, "while"},
            {Keyword::IF, "if"},
            {Keyword::ELSE, "else"},
            {Keyword::OPEN_BRACKET, "("},
            {Keyword::CLOSE_BRACKET, ")"},
            {Keyword::OPEN_CURLY_BRACE, "{"},
            {Keyword::CLOSE_CURLY_BRACE, "}"},
            {Keyword::SEMICOLON, ";"},
            {Keyword::ASSIGN, "assign"},
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
            {Keyword::OR, "||"}
    };
}
