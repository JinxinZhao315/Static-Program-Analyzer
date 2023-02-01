#include<stdio.h>
#include "Tokens.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

map<int, int> nesting_level;

bool findToken(std::string s) {
    auto it = Tokens::TOKEN_MAP.find(s);
    if (it != Tokens::TOKEN_MAP.end()) {
        return true;
    } else {
        return false;
    }
}

bool emptyToken(std::string token) {
    if(token == "" || token == " ") {
        return true;
    } else {
        return false;
    }
}

std::vector<std::string> pushToken(std::vector<std::string> tokens, std::string token) {
    if(!emptyToken(token)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> tokenise(std::string line) {
    std::vector<std::string> tokens;
    std::string currentToken = "";
    for(char c : line) {
        std:string s(1, c);
        if(findToken(s)) {
            tokens = pushToken(tokens, currentToken);
            tokens = pushToken(tokens, s);
            currentToken = "";
        } else if (c == ' ') {
            tokens = pushToken(tokens, currentToken);
            currentToken = "";
        } else {
            currentToken += c;
        }
    }
    return tokens;
}

void processFile(std::ifstream &file) {
    string curr_line;
    int line_number;
    int curr_level;

    curr_level = 1;
    line_number = 1;
    // Parse the SIMPLE program line by line
    while (getline(file, curr_line)) {
        line_number++;
        cout << curr_line << endl;
        for (char c : curr_line) {
            if (c == '{') {
                curr_level++;
            } else if (c == '}') {
                curr_level--;
            }
        }
        nesting_level[line_number] = curr_level;
    }
    cout << nesting_level[line_number];
}

int main() {
    std::vector<std::string> tokens = tokenise("procedure computeAverage() { read x; print x; } ");
    for (std::string token : tokens) {
        cout << token << endl;
    }
}
