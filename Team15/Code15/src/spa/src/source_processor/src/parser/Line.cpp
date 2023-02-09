#include "../../include/parser/Line.h"

int Line::getLineNumber() {
    return lineNumber;
}

vector<string> Line::getTokens() {
    return tokens;
}

string Line::getType() {
    return type;
}


