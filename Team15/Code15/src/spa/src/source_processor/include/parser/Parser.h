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
    void parseProgram(const string& fileName);
    void printParsedProgram();
    vector<string> getParsedProgram();
private:
    vector<string> parsedFile;
    void reformatParsedProgram();
    static vector<string> separateLines(string str);
    static void removeWhiteSpaces(string &str);
};
