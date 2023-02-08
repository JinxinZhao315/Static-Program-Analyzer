#pragma once

#include <string>
#include <vector>

using namespace std;

class Line {
private:
    int lineNumber;
    vector<string> content;
public:
    Line(int lineNumber, vector<string> content);
    int getLineNumber();
    vector<string> getContent();
};