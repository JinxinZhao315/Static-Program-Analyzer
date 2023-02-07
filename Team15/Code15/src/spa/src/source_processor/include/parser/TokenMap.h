#include <map>
#include <string>
#include <utility>
#include "Tokens.h"

class TokenMap {
private:
    inline static const std::map<std::string , Tokens::Keyword> TOKEN_MAP = {
            {"procedure", Tokens::Keyword::PROCEDURE},
            {"while", Tokens::Keyword::WHILE},
            {"if", Tokens::Keyword::IF},
            {"else", Tokens::Keyword::ELSE},
            {"(", Tokens::Keyword::OPEN_BRACKET},
            {")", Tokens::Keyword::CLOSE_BRACKET, },
            {"{", Tokens::Keyword::OPEN_CURLY_BRACE},
            {"}", Tokens::Keyword::CLOSE_CURLY_BRACE},
            {";", Tokens::Keyword::SEMICOLON},
            {"=", Tokens::Keyword::ASSIGN},
            {"read", Tokens::Keyword::READ},
            {"call", Tokens::Keyword::CALL},
            {"print", Tokens::Keyword::PRINT},
            {"+", Tokens::Keyword::ADD},
            {"-", Tokens::Keyword::SUBTRACT},
            {"*", Tokens::Keyword::MULTIPLY},
            {"/", Tokens::Keyword::DIVIDE},
            {"%", Tokens::Keyword::MODULO},
            {">", Tokens::Keyword::GT},
            {">=", Tokens::Keyword::GTE},
            {"<", Tokens::Keyword::LT},
            {"<=", Tokens::Keyword::LTE},
            {"==", Tokens::Keyword::EQUAL},
            {"!=", Tokens::Keyword::NOT_EQUAL},
            {"!", Tokens::Keyword::NOT},
            {"&&", Tokens::Keyword::AND},
            {"||",Tokens::Keyword::OR}
    };

    inline static const std::map<Tokens::Keyword, std::string> STRING_MAP = {
            {Tokens::Keyword::PROCEDURE, "procedure"},
            {Tokens::Keyword::WHILE, "while"},
            {Tokens::Keyword::IF, "if"},
            {Tokens::Keyword::ELSE, "else"},
            {Tokens::Keyword::OPEN_BRACKET, "("},
            {Tokens::Keyword::CLOSE_BRACKET, ")" },
            {Tokens::Keyword::OPEN_CURLY_BRACE, "{"},
            {Tokens::Keyword::CLOSE_CURLY_BRACE, "}"},
            {Tokens::Keyword::SEMICOLON, ";"},
            {Tokens::Keyword::ASSIGN, "="},
            {Tokens::Keyword::READ, "read"},
            {Tokens::Keyword::CALL, "call"},
            {Tokens::Keyword::PRINT, "print"},
            {Tokens::Keyword::ADD, "+"},
            {Tokens::Keyword::SUBTRACT, "-"},
            {Tokens::Keyword::MULTIPLY, "*"},
            {Tokens::Keyword::DIVIDE, "/"},
            {Tokens::Keyword::MODULO, "%"},
            {Tokens::Keyword::GT, ">"},
            {Tokens::Keyword::GTE, ">="},
            {Tokens::Keyword::LT, "<"},
            {Tokens::Keyword::LTE, "<="},
            {Tokens::Keyword::EQUAL, "=="},
            {Tokens::Keyword::NOT_EQUAL, "!="},
            {Tokens::Keyword::NOT, "!"},
            {Tokens::Keyword::AND, "&&"},
            {Tokens::Keyword::OR,"||"}
    };

    std::pair<std::map<Tokens::Keyword, std::string>, std::map<std::string, Tokens::Keyword>> doubleKeyedTokenMap = std::make_pair(STRING_MAP, TOKEN_MAP);

public:
    TokenMap();

    Tokens::Keyword getTokenByString(std::string token);

    std::string getStringByToken(Tokens::Keyword keyword);

    bool tokenExistsByString(std::string s);

    bool stringExistsByToken(Tokens::Keyword keyword);
};