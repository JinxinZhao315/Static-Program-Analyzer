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

public:
    Tokeniser();
    void feedLines(string filename);
    vector<string>* keywords;
    vector<string>* tokenise(string line);
};
