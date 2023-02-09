#pragma once

#include <string>
#include <vector>

using namespace std;

class Line {
private:
    int lineNumber;
    vector<string> tokens;
public:
    Line(int lineNumber, vector<string> tokens);
    int getLineNumber();
    vector<string> getTokens();
};