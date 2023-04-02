#include "source_processor/include/tokeniser/Tokeniser.h"

Tokeniser::Tokeniser() {
    keywords = new Keywords();
}

void Tokeniser::feedLines(const vector<string>& lines) {
    auto* tokenVector = new vector<vector<string>*>();
    for(const auto& line : lines) {
        vector<string>* tokens = tokenise(line);
        tokenVector->push_back(tokens);
    }
    extractedTokens = tokenVector;
    generateLineObjects(extractedTokens);
}

void pushToken(vector<string>* tokens, const string& token) {
    tokens->push_back(token);
}

bool Tokeniser::passesLengthCheck(const string& keyword, const string& token) const {
    if(keyword == keywords->keywordMap.second.at(READ)
        || keyword == keywords->keywordMap.second.at(PRINT)
        || keyword == keywords->keywordMap.second.at(CALL)
        || keyword == keywords->keywordMap.second.at(PROCEDURE)
        || keyword == keywords->keywordMap.second.at(WHILE)
        || keyword == keywords->keywordMap.second.at(IF)
        || keyword == keywords->keywordMap.second.at(THEN)
        || keyword == keywords->keywordMap.second.at(ELSE)
        || keyword == keywords->keywordMap.second.at(RETURN)
        || keyword == keywords->keywordMap.second.at(TRUE)
        || keyword == keywords->keywordMap.second.at(FALSE)
        ) {
        return keyword.length() == token.length();
    } else {
        return true;
    }
}

bool Tokeniser::setStartsWithKeyword(vector<string>* keywordVector, vector<string>* tokens, const string& token, int* position) const {
    bool isKeyword = false;
    for (const auto& keyword : *keywordVector) {
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

int Tokeniser::setNextKeywordPosition(vector<string>* keywordVector, const string& token, int currentPosition) const {
    int nextKeywordPosition = token.length();
    for (const auto& keyword : *keywordVector) {
        int keywordPosition = token.find(keyword, currentPosition);
        if (keywordPosition != -1 && keywordPosition < nextKeywordPosition && passesLengthCheck(keyword, token)) {
            nextKeywordPosition = keywordPosition;
        }
    }
    return nextKeywordPosition;
}

void Tokeniser::moveToNextKeyword(vector<string>* keywordVector, vector<string>* tokens, const string& token, int* currentPosition) const {
    int nextKeywordPosition = setNextKeywordPosition(keywordVector, token, *currentPosition);
    int nonKeywordTokenLength = nextKeywordPosition - *currentPosition;
    string nonKeywordToken = token.substr(*currentPosition, nonKeywordTokenLength);
    pushToken(tokens, nonKeywordToken);
    *currentPosition = nextKeywordPosition;
}

vector<string>* Tokeniser::tokenise(const string& line) const {
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

KeywordsEnum Tokeniser::findKeyword(vector<string>* line) const {
    for (const auto& token : *line) {
        if(keywords->keywordMap.first.count(token) > 0) {
            return keywords->keywordMap.first.at(token);
        }
    }
    return NONE;
}

bool checkKeywordHasLineNumber(KeywordsEnum keyword) {
    return !(keyword == PROCEDURE || keyword == ELSE || keyword == CLOSE_CURLY);
}

bool checkElse(vector <string>* line) {
    return find(line->begin(), line->end(), "}") != line->end()
           && find(line->begin(), line->end(), "else") != line->end();
}

void Tokeniser::generateLineObjects(vector<vector<string> *> *tokens) {
    int lineNumber = 1;
    vector<Line> lines;
    for(auto line : *tokens) {
        KeywordsEnum keyword = findKeyword(line);
        bool hasLineNumber = checkKeywordHasLineNumber(keyword);
        Line* extractedLine;
        if(hasLineNumber) {
            extractedLine = new Line(lineNumber, *line, keyword);
            lineNumber++;
        } else {
            extractedLine = new Line(*line, keyword);
            if(checkElse(line)) {
                extractedLine = new Line(*line, ELSE);
            }
        }
        lines.push_back(*extractedLine);
    }
    // TODO: pkb.storeAllLines(lines);
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
