#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm>
#include "common/include/models/Line.h"
#include "common/include/models/Keywords.h"

using namespace std;

class Tokeniser {
private:
    vector<vector<string>*>* extractedTokens;
    vector<Line> extractedLines;
public:
    Tokeniser();
    void feedLines(const vector<string>& lines);
    KeywordsEnum findKeyword(vector<string>* line) const;
    bool passesLengthCheck(const string& keyword, const string& token) const;
    bool setStartsWithKeyword(vector<string>* keywords, vector<string>* tokens, const string& token, int* position) const;
    int setNextKeywordPosition(vector<string>* keywords, const string& token, int currentPosition) const;
    void moveToNextKeyword(vector<string>* keywords, vector<string>* tokens, const string& token, int* currentPosition) const;
    Keywords* keywords;
    vector<string>* tokenise(const string& line) const;
    void printTokens();
    void printLines();
    void generateLineObjects(vector<vector<string>*>* tokens);
    vector<Line> getExtractedLines();
};
