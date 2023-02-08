#include "../../include/parser/Parser.h"

using namespace std;

void Parser::printParsedProgram() {
    cout << "Parsed file:" << endl;
    for (const auto &line : parsedFile) {
        std::cout << line << endl;
    }
    cout << "End of file:" << endl;

}
void Parser::parseProgram(string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Failed to open file: " << fileName << endl;
    }

    string currLine;
    // Parse the SIMPLE program line by line
    while (getline(file, currLine)) {
        Parser::removeWhiteSpaces(currLine);
        vector<string> newLines = separateLines(currLine);
        parsedFile.insert(parsedFile.end(),  newLines.begin(), newLines.end());
    }
    file.close();
}

void Parser::removeWhiteSpaces(string &str) {
    str.erase (remove (str.begin(), str.end(), ' '), str.end());
}

vector<string> Parser::separateLines(string str) {
    vector<string> lines;
    string line;
    for (char c: str) {
        if (c == '{' || c == '}' || c == ';') {
            line += c;
            lines.push_back(line);
            line.clear();
        } else {
            line += c;
        }
    }
    if (!line.empty()) {
        lines.push_back(line);
    }
    return lines;
}


vector<string> Parser::getParsedProgram() {
    return this->parsedFile;
}