#pragma once

#include <string>
#include <vector>

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
    };
    Line(int lineNumber, vector<string> tokens, string type) {
        this->lineNumber = lineNumber;
        this->tokens = tokens;
        this->type = type;
    }

    int getLineNumber();
    vector<string> getTokens();
    string getType();
};