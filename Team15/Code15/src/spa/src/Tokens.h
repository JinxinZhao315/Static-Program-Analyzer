#pragma once

#include <map>
#include <string>
#include <utility>

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

    class TokenMap {
    private:
        std::pair<std::map<Keyword, std::string>, std::map<std::string, Keyword>> doubleKeyedTokenMap;
    public:
        TokenMap();

        void setMap(std::map<Keyword, std::string> mapToString, std::map<std::string, Keyword> mapToKeyword);

        Keyword getTokenByString(std::string token);

        std::string getStringByToken(Keyword keyword);
    };
}
