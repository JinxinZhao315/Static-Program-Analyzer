#include<stdio.h>
#include "Tokens.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <climits>

using namespace std;
using namespace Tokens;

void generateFollowsRS();
void generateNestingLevel();

map<int, vector<string>> parsed;
map<int, int> nesting_level;
map<int, int> follows;
map<int, vector<int> > follows_star;

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
    vector<std::string> tokens;
    string currentToken = "";
    for(char c : line) {
        string s(1, c);
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
    // Parse the SIMPLE program line by line
    int line_number;
    line_number = 1;
    while (getline(file, curr_line)) {
        parsed[line_number] = tokenise(curr_line);
        line_number++;
    }
    generateNestingLevel();
    generateFollowsRS();
}

void generateNestingLevel() {
    int curr_level;
    curr_level = 0;
    for (auto it = parsed.begin(); it != parsed.end(); ++it) {
        int line_number = it->first;
        vector<std::string> tokens = it->second;
        int final_nesting_level = 0;
        for (int i = 0; i < tokens.size(); i++) {
            string token = tokens[i];
            if (token == "procedure") {
                final_nesting_level = 0;
                curr_level = 0;
            } else if (token == ";") {
                final_nesting_level = curr_level;
            } else if (token == "}" && i == 0) { // starts with opening brace
                curr_level--;
                final_nesting_level = curr_level;
            } else if (token == "{") {
                final_nesting_level = curr_level;
                curr_level++;
            } else if (token == "}") {
                curr_level--;
            }
        }
        if (tokens.size() == 0) {
            final_nesting_level = -1;
        }
        nesting_level[line_number] = final_nesting_level;

    }
    for (const auto &pair : nesting_level) {
        std::cout << "Line number: " << pair.first << ", Nesting level: " << pair.second << std::endl;
    }
    cout << endl;
}

void generateFollowsRS() {
    for (auto outer_it = nesting_level.begin(); outer_it != nesting_level.end(); ++outer_it) {
        for (auto inner_it = next(outer_it); inner_it != nesting_level.end(); ++inner_it) {
            int first_line_number = outer_it->first;
            int second_line_number = inner_it->first;
            int first_nesting_level = outer_it->second;
            int second_nesting_level = inner_it->second;
            if (second_nesting_level == -1) { // new procedure
                break;
            }
            // For follows rs
            bool is_line_after = second_line_number == first_line_number + 1;
            bool is_same_nesting_level = first_nesting_level == second_nesting_level;
            if (is_line_after && is_same_nesting_level) { // Line right after is same indentation -> follows
                follows[first_line_number] = second_line_number;
            }

            // For follows* rs
            if (first_nesting_level == second_nesting_level) {
                if (follows_star.count(first_line_number)) {
                    follows_star[first_line_number].push_back(second_line_number);
                } else {
                    vector<int> new_vector;
                    new_vector.push_back(second_line_number);
                    follows_star.insert(make_pair(first_line_number, new_vector));
                }
            }
        }
    }
    for (auto it = follows_star.begin(); it != follows_star.end(); ++it) {
        cout << it->first << ": [";
        for (int i : it->second) {
            cout << i << ", ";
        }
        cout << "]" << endl;
    }
}

int main(int argc, char* argv[]) {
    // For early testing this filepath is temporarily hard coded
    string filename = "Team15/Tests15/Sample_source.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return 0;
    }
    processFile(file);

    file.close();
    return 0;
}