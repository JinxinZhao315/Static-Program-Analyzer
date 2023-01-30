#include<stdio.h>
//#include "Tokens.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

map<int, int> nesting_level;

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