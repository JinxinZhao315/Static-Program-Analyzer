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
    Parser(const std::string &fileName)
            : fileName(fileName) { }
    void parseProgram();
    void removeWhiteSpaces(string &str);
    vector<string> getParsedProgram();
    vector<string> separateLines(string str);
private:
    string fileName;
    vector<string> parsedFile;
};

//    string toString() const {
//        stringstream ss;
//        ss << "Parser with fileName: " << fileName;
//        return ss.str();
//    }
