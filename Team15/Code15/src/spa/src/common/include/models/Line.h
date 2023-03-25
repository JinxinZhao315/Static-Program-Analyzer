#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Line {
private:
    int lineNumber;
    vector<string> tokens;
    string type;
public:
    Line(int lineNumber, vector<string> tokens) {
        this->lineNumber = lineNumber;
        this->tokens = tokens;
        this->type= "";
    };
    Line(int lineNumber, vector<string> tokens, string type) {
        this->lineNumber = lineNumber;
        this->tokens = tokens;
        this->type = type;
    }
    Line(vector<string> tokens, string type) {
        this->lineNumber = 0;
        this->tokens = tokens;
        this->type = type;
    }

    int getLineNumber() const;
    vector<string> getTokens();
    string getType() const;
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
