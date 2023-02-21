#include "source_processor/include/tokeniser/Tokeniser.h"

Tokeniser::Tokeniser() {
    keywords = new Keywords();
}

void Tokeniser::feedLines(vector<string> lines) {
    auto* tokenVector = new vector<vector<string>*>();
    for(auto line : lines) {
        vector<string>* tokens = tokenise(line);
        tokenVector->push_back(tokens);
    }
    extractedTokens = tokenVector;
    generateLineObjects(extractedTokens);
}

void Tokeniser::printTokens() {
    for(vector<string>* line : *extractedTokens) {
        for(const string& token : *line) {
            cout << token << " ";
        }
        cout << endl;
    }
}

void pushToken(vector<string>* tokens, string token) {
    tokens->push_back(token);
}

bool passesLengthCheck(string keyword, string token) {
    if(keyword == "read"
        || keyword == "print"
        || keyword == "call"
        || keyword == "procedure"
        || keyword == "while"
        || keyword == "if"
        || keyword == "then"
        || keyword == "else"
        || keyword == "return"
        || keyword == "true"
        || keyword == "false"
        ) {
        return keyword.length() == token.length();
    } else {
        return true;
    }
}

bool setStartsWithKeyword(vector<string>* keywords, vector<string>* tokens, string token, int* position) {
    bool isKeyword = false;
    for (auto keyword : *keywords) {
        int keywordLength = keyword.length();
        if (token.find(keyword, *position) == *position && passesLengthCheck(keyword, token)) {

            isKeyword = true;
            pushToken(tokens, keyword);
            *position += keywordLength;
            break;
        }
    }
    return isKeyword;
}

int setNextKeywordPosition(vector<string>* keywords, string token, int currentPosition) {
    int nextKeywordPosition = token.length();
    for (auto keyword : *keywords) {
        int keywordPosition = token.find(keyword, currentPosition);
        if (keywordPosition != -1 && keywordPosition < nextKeywordPosition && passesLengthCheck(keyword, token)) {
            nextKeywordPosition = keywordPosition;
        }
    }
    return nextKeywordPosition;
}

void moveToNextKeyword(vector<string>* keywords, vector<string>* tokens, string token, int* currentPosition) {
    int nextKeywordPosition = setNextKeywordPosition(keywords, token, *currentPosition);
    int nonKeywordTokenLength = nextKeywordPosition - *currentPosition;
    string nonKeywordToken = token.substr(*currentPosition, nonKeywordTokenLength);
    pushToken(tokens, nonKeywordToken);
    *currentPosition = nextKeywordPosition;
}

vector<string>* Tokeniser::tokenise(string line) {
    auto* tokens = new vector<string>();
    stringstream stream(line);
    string token;
    while(stream >> token) {
        int currentPosition = 0;
        while(currentPosition < token.length()) {
            bool startsWithKeyword = setStartsWithKeyword(keywords->getKeywords(), tokens, token, &currentPosition);
            if (!startsWithKeyword) moveToNextKeyword(keywords->getKeywords(), tokens, token, &currentPosition);
        }
    }
    return tokens;
}

string findKeyword(vector<string>* line, vector<string>* keywords) {
    for (auto token : *line) {
        if (find(keywords->begin(), keywords->end(), token) != keywords->end()) {
            return token;
        }
    }
    return "";
}

bool checkKeywordHasLineNumber(string keyword) {
    return !(keyword == "procedure" || keyword == "else" || keyword == "}");
}

bool checkElse(vector <string>* line) {
    return find(line->begin(), line->end(), "}") != line->end()
           && find(line->begin(), line->end(), "else") != line->end();
}

void Tokeniser::generateLineObjects(vector<vector<string> *> *tokens) {
    int lineNumber = 1;
    vector<Line> lines;
    for(auto line : *tokens) {
        string keyword = findKeyword(line, keywords->getKeywords());
        bool hasLineNumber = checkKeywordHasLineNumber(keyword);
        Line* extractedLine;
        if(hasLineNumber) {
            extractedLine = new Line(lineNumber, *line, keyword);
            lineNumber++;
        } else {
            extractedLine = new Line(*line, keyword);
            if(checkElse(line)) {
                extractedLine = new Line(*line, "else");
            }
        }
        lines.push_back(*extractedLine);
    }
    this->extractedLines = lines;
}

vector<Line> Tokeniser::getExtractedLines() {
    return this->extractedLines;
}

void Tokeniser::printLines() {
    for(auto line: extractedLines) {
        line.printLine();
    }
    cout << endl;
}
