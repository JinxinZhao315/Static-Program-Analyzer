#include "../../include/parser/Parser.h"

using namespace std;

void Parser::parseProgram() {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Failed to open file: " << fileName << endl;
    }

    string currLine;
    // Parse the SIMPLE program line by line
    while (getline(file, currLine)) {

        vector<string> newLines = separateLines(currLine);
        parsedFile.insert(parsedFile.end(),  newLines.begin(), newLines.end());
    }
    file.close();
}

void removeWhiteSpaces(string &str) {
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

int main() {
    Parser parser("Team15/Tests15/Sample_source.txt");
    parser.parseProgram();
    vector<string> result = parser.getParsedProgram();
    for (const auto &line : result) {
        std::cout << line << endl;
    }
    std::cout << std::endl;
}