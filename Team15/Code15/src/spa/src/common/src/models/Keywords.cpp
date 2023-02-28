#include "common/include/models/Keywords.h"

Keywords::Keywords() {
    auto* keys = new vector<string>();
    *keys = {
            "procedure",
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

vector<string> *Keywords::getKeywords() {
    return this->keywords;
}
