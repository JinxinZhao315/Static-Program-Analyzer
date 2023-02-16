#pragma once
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

class Parser {
public:
    Parser() {}
    void parseProgram(string fileName);
    void printParsedProgram();
    vector<string> getParsedProgram();
private:
    vector<string> parsedFile;
    vector<string> separateLines(string str);
    void removeWhiteSpaces(string &str);
};
