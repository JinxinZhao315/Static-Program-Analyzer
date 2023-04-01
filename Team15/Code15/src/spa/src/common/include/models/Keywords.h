#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

enum KeywordsEnum {
    PROCEDURE,
    WHILE,
    IF,
    THEN,
    ELSE,
    OPEN_CURLY,
    CLOSE_CURLY,
    OPEN_PAREN,
    CLOSE_PAREN,
    SEMICOLON,
    ASSIGN,
    READ,
    CALL,
    PRINT,
    PLUS,
    TIMES,
    DIVIDE,
    MINUS,
    MODULO,
    GT,
    LT,
    GTE,
    LTE,
    EQUAL,
    NOT_EQUAL,
    AND,
    OR,
    NOT,
    RETURN,
    TRUE,
    FALSE,
    NONE,
};

class Keywords {
public:
    Keywords();
    pair<map<string, KeywordsEnum>, map<KeywordsEnum, string>> keywordMap;
    vector<string>* getKeywords();
    bool isKeyword(string token);
private:
    vector<string>* keywords;
};