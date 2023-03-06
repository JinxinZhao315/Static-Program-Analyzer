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

string Parser::removeAllWhitespace(std::string str) {
    // use std::remove_if() with std::isspace() to remove all white space characters
    str.erase(remove_if(str.begin(), str.end(), [](unsigned char c) { return isspace(c); }), str.end());
    return str;
}

vector<string> Parser::separateLines(string str) {
    vector<string> lines;
    string line;
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        if (c == '{' || c == '}' || c == ';') {
            line += c;
            lines.push_back(line);
            line.clear();
            if (i + 1 < str.size() && str[i + 1] == ' ') {
                i++;
            }
        } else {
            line += c;
        }
    }
    if (!line.empty()) {
        lines.push_back(line);
    }
    return lines;
}

string Parser::trimStartingAndTrailingWhitespace(const string& str) {
    auto firstValid = str.find_first_not_of(" \t\n\r\f\v");
    if (firstValid == std::string::npos) {
        return "";
    }
    auto lastValid = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(firstValid, lastValid - firstValid + 1);
}

void Parser::reformatParsedProgram() {
    int len = (int) this->parsedFile.size();
    if (len < 2) {
        return;
    }
    vector<string> formattedFile;
    for (int i = 0; i < len; i++) {
        string line = this->parsedFile[i];
        if (i < len - 1) {
            string nextLine = this->parsedFile[i + 1];
            if (removeAllWhitespace(line) == "}" && removeAllWhitespace(nextLine) == "else{") {
                formattedFile.emplace_back("} else {");
                i++;
            } else {
                formattedFile.push_back(trimStartingAndTrailingWhitespace(line));
            }
        } else {
            formattedFile.push_back(trimStartingAndTrailingWhitespace(line));
        }
    }
    this->parsedFile = formattedFile;
}
vector<string> Parser::getParsedProgram() {
    return this->parsedFile;
}