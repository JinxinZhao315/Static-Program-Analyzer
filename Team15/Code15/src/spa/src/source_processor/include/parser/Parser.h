#pragma once
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <stdio.h>
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

class Parser {
public:
    Parser();
    void parseProgram(string fileName);
    void printParsedProgram();
    vector<string> getParsedProgram();
private:
    vector<string> parsedFile;
    vector<string> separateLines(string str);
    void removeWhiteSpaces(string &str);
};
