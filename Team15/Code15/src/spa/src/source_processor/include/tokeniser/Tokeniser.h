#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

class Tokeniser {
private:
    vector<vector<string>*>* extractedTokens;
public:
    Tokeniser();
    vector<vector<string>*>* feedLines(string filename);
    vector<string>* keywords;
    vector<string>* tokenise(string line);
    void printTokens();
};
