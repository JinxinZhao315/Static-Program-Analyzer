#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm>
#include "../parser/Line.h"

using namespace std;

class Tokeniser {
private:
    vector<vector<string>*>* extractedTokens;
    vector<Line> extractedLines;
public:
    Tokeniser();
    void feedLines(string filename);
    vector<string>* keywords;
    vector<string>* tokenise(string line);
    void printTokens();
    void printLines();
    void generateLineObjects(vector<vector<string>*>* tokens);
    vector<Line> getExtractedLines();
};
