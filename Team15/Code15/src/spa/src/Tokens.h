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
        MODULO
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
            {Keyword::READ, ";"},
            {Keyword::CALL, ";"},
            {Keyword::PRINT, ";"},
            {Keyword::ADD, "+"},
            {Keyword::SUBTRACT, "-"},
            {Keyword::MULTIPLY, "*"},
            {Keyword::DIVIDE, "/"},
    };
}
