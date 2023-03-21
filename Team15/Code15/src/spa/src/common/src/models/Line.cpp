#include "common/include/models/Line.h"

#include <iostream>

using namespace std;

int Line::getLineNumber() {
    return lineNumber;
}

vector<string> Line::getTokens() {
    return tokens;
}

string Line::getType() const {
    return type;
}

void Line::printLine() {
    cout << this->lineNumber << ": " << this->type << endl;
}
