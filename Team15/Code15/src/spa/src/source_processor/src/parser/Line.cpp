#include "../../include/parser/Line.h"

Line::Line(int lineNumber, vector<string> content) {
    this->lineNumber = lineNumber;
    this->content = content;
}

int Line::getLineNumber() {
    return lineNumber;
}

vector<string> Line::getContent() {
    return content;
}
