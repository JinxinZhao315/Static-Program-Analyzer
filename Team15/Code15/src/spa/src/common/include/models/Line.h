#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Keywords.h"

using namespace std;

class Line {
private:
    int lineNumber;
    vector<string> tokens;
    KeywordsEnum type;
public:
    Line() {};
    Line(int lineNumber, vector<string> tokens) {
        this->lineNumber = lineNumber;
        this->tokens = tokens;
        this->type = NONE;
    };
    Line(int lineNumber, vector<string> tokens, KeywordsEnum type) {
        this->lineNumber = lineNumber;
        this->tokens = tokens;
        this->type = type;
    }
    Line(vector<string> tokens, KeywordsEnum type) {
        this->lineNumber = 0;
        this->tokens = tokens;
        this->type = type;
    }

    int getLineNumber() const;
    vector<string> getTokens();
    KeywordsEnum getType() const;
    void printLine();

    bool operator<(const Line& l) const { // necessary to create set<Line>
        return lineNumber < l.lineNumber;
    }

    bool operator==(const Line& l) const { // necessary to create set<Line>
        if(lineNumber != l.lineNumber || type != l.type) return false;
        for(int i = 0; i < tokens.size(); i++) {
            string token = tokens[i];
            string other = l.tokens[i];
            if(token != other) {
                return false;
            }
        }
        return true;
    }
};
