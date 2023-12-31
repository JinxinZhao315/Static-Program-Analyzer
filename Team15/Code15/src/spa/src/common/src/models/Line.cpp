#include "common/include/models/Line.h"

#include <iostream>

using namespace std;

int Line::getLineNumber() const {
    return lineNumber;
}

vector<string> Line::getTokens() {
    return tokens;
}

KeywordsEnum Line::getType() const {
    return type;
}

void Line::printLine() {
    cout << this->lineNumber << ": " << this->type << endl;
}
