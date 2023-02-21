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
    void feedLines(vector<string> lines);
    Keywords* keywords;
    vector<string>* tokenise(string line);
    void printTokens();
    void printLines();
    void generateLineObjects(vector<vector<string>*>* tokens);
    vector<Line> getExtractedLines();
};
