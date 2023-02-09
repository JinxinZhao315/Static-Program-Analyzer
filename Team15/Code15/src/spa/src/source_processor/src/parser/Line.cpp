#include "../../include/parser/Line.h"

Line::Line(int lineNumber, vector<string> tokens) {
    this->lineNumber = lineNumber;
    this->tokens = tokens;
}

int Line::getLineNumber() {
    return lineNumber;
}

vector<string> Line::getTokens() {
    return tokens;
}
