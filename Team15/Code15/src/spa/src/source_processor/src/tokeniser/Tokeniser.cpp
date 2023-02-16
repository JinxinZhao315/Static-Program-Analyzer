#include "../../include/tokeniser/Tokeniser.h"

Tokeniser::Tokeniser() {
    vector<string>* keys = new vector<string>();
    *keys = {
            "procedure",
            "while",
            "if",
            "else",
            "{",
            "}",
            "(",
            ")",
            ";",
            "=",
            "read",
            "call",
            "print",
            "+",
            "*",
            "/",
            "-",
            "%",
            ">",
            "<",
            ">=",
            "<=",
            "==",
            "!=",
            "&&",
            "||",
            "!",
            "return",
            "true",
            "false"
    };
    keywords = keys;
    sort(keywords->begin(), keywords->end(), [](auto first, auto second) {
        return second.length() < first.length();
    });
}

void Tokeniser::feedLines(string filename) {
    vector<vector<string>*>* tokenVector = new vector<vector<string>*>();
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
    }
    string line;
    while(getline(file, line)) {
        vector<string>* tokens = tokenise(line);
        tokenVector->push_back(tokens);
    }
    extractedTokens = tokenVector;
    generateLineObjects(extractedTokens);
}

void Tokeniser::printTokens() {
    for(vector<string>* line : *extractedTokens) {
        for(string token : *line) {
            cout << token << " ";
        }
        cout << endl;
    }
}

void pushToken(vector<string>* tokens, string token) {
    tokens->push_back(token);
}

bool setStartsWithKeyword(vector<string>* keywords, vector<string>* tokens, string token, int* position) {
    bool isKeyword = false;
    for (auto keyword : *keywords) {
        if (token.find(keyword, *position) == *position) {
            isKeyword = true;
            pushToken(tokens, keyword);
            int keywordLength = keyword.length();
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
        if (keywordPosition != -1 && keywordPosition < nextKeywordPosition) {
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
    vector<string>* tokens = new vector<string>();
    stringstream stream(line);
    string token;
    while(stream >> token) {
        int currentPosition = 0;
        while(currentPosition < token.length()) {
            bool startsWithKeyword = setStartsWithKeyword(keywords, tokens, token, &currentPosition);
            if (!startsWithKeyword) moveToNextKeyword(keywords, tokens, token, &currentPosition);
        }
    }
    return tokens;
}

string findKeyword(vector<string>* line, vector<string>* keywords) {
    bool extracted = false;
    string extractedKeyword = "";
    for(auto token : *line) {
        for(auto keyword: *keywords) {
            if(token == keyword) {
                extracted = true;
                extractedKeyword = keyword;
                break;
            }
        }
        if(extracted) {
            break;
        }
    }
    return extractedKeyword;
}

bool checkKeywordHasLineNumber(string keyword) {
    if(keyword == "procedure" || keyword == "else") {
        return false;
    } else {
        return true;
    }
}

void Tokeniser::generateLineObjects(vector<vector<string> *> *tokens) {
    int lineNumber = 1;
    vector<Line> extractedLines;
    for(auto line : *tokens) {
        string keyword = findKeyword(line, keywords);
        bool hasLineNumber = checkKeywordHasLineNumber(keyword);
        Line* extractedLine;
        if(hasLineNumber) {
            extractedLine = new Line(lineNumber, *line, keyword);
            lineNumber++;
        } else {
            extractedLine = new Line(*line, keyword);
        }
        extractedLines.push_back(*extractedLine);
    }
    this->extractedLines = extractedLines;
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
