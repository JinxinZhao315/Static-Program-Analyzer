#include "source_processor/include/parser/Parser.h"
#include <regex>

using namespace std;

void Parser::printParsedProgram() {
    cout << "--- Parsed file ---" << endl;
    for (const auto &line : parsedFile) {
        std::cout << line << endl;
    }
    cout << "--- End of file ---" << endl;

}
void Parser::parseProgram(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Failed to open file: " << fileName << endl;
    }

    string currLine;
    // Parse the SIMPLE program line by line
    while (getline(file, currLine)) {
        removeWhiteSpaces(currLine);
        vector<string> newLines = separateLines(currLine);
        parsedFile.insert(parsedFile.end(),  newLines.begin(), newLines.end());
    }
    reformatParsedProgram();
    file.close();
}

void Parser::removeWhiteSpaces(string &str) {
    regex pattern("\\s+");
    string result = regex_replace(str, pattern, " ");
    str = result;
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

void Parser::reformatParsedProgram() {
    int len = (int) this->parsedFile.size();
    if (len < 2) {
        return;
    }
    vector<string> formattedFile;
    for (int i = 0; i < len; i++) {
        string line = this->parsedFile[i];
        string nextLine = this->parsedFile[i + 1];
        if (i < len - 1 && line == "}" && nextLine == "else {") {
            formattedFile.emplace_back("} else {");
        } else {
            formattedFile.push_back(line);
        }
    }
    this->parsedFile = formattedFile;
}
vector<string> Parser::getParsedProgram() {
    return this->parsedFile;
}