#include <stdio.h>
#include "Tokens.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <set>

using namespace std;
using namespace Tokens;

void generateFollowsRS();
void generateNestingLevel();
void generateAssignmentRS();
std::vector<std::string> convertToPostfix(std::vector<std::string> tokens, int startIndex);

map<int, vector<string>> parsed;
map<int, int> nesting_level;
map<int, int> follows;
map<int, vector<int> > follows_star;
map<string, vector<vector<string>>> assigns;

set<string> procedures;
vector<string> constants;
set<string> variables;
map<Tokens::Keyword, vector<int>> statements;

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

bool isNumeric(const std::string token) {
    for (char c : token) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isStatement(std::string token) {
    return token == "read"
        || token == "print"
        || token == "call"
        || token == "while"
        || token == "if"
        || token == "assign";
}

Tokens::Keyword getStatementType(std::string token) {
    return TOKEN_MAP[token];
}

void extract(std::vector<std::string> tokens, int lineNumber) {
    for(int i = 0; i < tokens.size(); ++i) {
        if(tokens[i] == "procedure") {
            procedures.insert(tokens[i+1]);
        } else if (isStatement(tokens[i])) {
            Tokens::Keyword statementType = getStatementType(tokens[i]);
            statements[statementType].push_back(lineNumber);
        } else if (isNumeric(tokens[i])) {
                constants.push_back(tokens[i]);
        } else if (i > 0 && tokens[i-1] == "=") {
            variables.insert(tokens[i]);
        }
    }
}

std::vector<std::string> tokenise(std::string line, int lineNumber) {
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
    extract(tokens, lineNumber);
    return tokens;
}

void processFile(std::ifstream &file) {
    string curr_line;
    // Parse the SIMPLE program line by line
    int line_number;
    line_number = 1;
    while (getline(file, curr_line)) {
        parsed[line_number] = tokenise(curr_line, line_number);
        line_number++;
    }
}

void generateNestingLevel() {
    int curr_level;
    curr_level = 0;
    for (auto it = parsed.begin(); it != parsed.end(); ++it) {
        int line_number = it->first;
        vector<string> tokens = it->second;
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
            if (is_same_nesting_level) {
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
    // print out follows relationship
    for (const auto& [key, value] : follows) {
        cout << "Follows relationship" << endl;
        cout << key << ": " << value << endl;
    }

    // print out follows* relationship
    cout << "Follows* relationship" << endl;
    for (auto it = follows_star.begin(); it != follows_star.end(); ++it) {
        cout << it->first << ": [";
        for (int i : it->second) {
            cout << i << ", ";
        }
        cout << "]" << endl;
    }
}
int precedence(string c) {
    if (c == "-" || c == "+") {
        return 1;
    } else if (c == "*" || c == "/" || c == "%") {
        return 2;
    } else if (c == "^") {
        return 3;
    }
    return -1;
}

bool isOperator(string c) {
    return precedence(c) > 0;
}

bool isNumber(string num) {
    try {
        stod(num);
        return true;
    } catch (const invalid_argument &e) {
        return false;
    }
}


vector<string> convertToPostfix(vector<string> tokens, int startIndex) {
    vector<string> result;
    stack<string> s;
    for (int i = startIndex; i < tokens.size(); i++) {
        string token = tokens[i];
        if (variables.count(token)) {
            result.push_back(token);
        } else if (isOperator(tokens[i])) {
            while (!s.empty() && precedence(s.top()) >= precedence(token)) {
                result.push_back(s.top());
                s.pop();
            }
            s.push(tokens[i]);
        } else if (isNumber(token)) {
            result.push_back(token);
        }
    }
    while (!s.empty()) {
        result.push_back(s.top());
        s.pop();
    }
    return result;
}

void generateAssignmentRS() {
    for (auto it = parsed.begin(); it != parsed.end(); ++it) {
        vector<string> tokens = it->second;
        string prev;
        string LHS;
        vector<string> RHS;
        int startIndexForRHS;
        bool hasRHS = false;
        for (int i = 0; i < tokens.size(); i++) {
            string token = tokens[i];
            if (token == "=") {
                LHS = prev;
                hasRHS = true;
                startIndexForRHS = i;
                break;
            }
            prev = token;
        }
        if (!hasRHS) {
            continue;
        }
        RHS = convertToPostfix(tokens, startIndexForRHS);
        if (assigns.count(LHS)) {
            assigns[LHS].push_back(RHS);
        } else {
            vector<vector<string>> new_vector;
            new_vector.push_back(RHS);
            assigns.insert(make_pair(LHS, new_vector));
        }
    }
    cout << "Assigns relationship" << endl;
    for (auto it = assigns.begin(); it != assigns.end(); ++it) {
        cout << it->first << ": [";
        for (auto match : it->second) {
            cout << "[";
            for (auto s: match) {
                cout << s << ", ";
            }
            cout << "]" << endl;
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
    generateNestingLevel();
    generateFollowsRS();
    generateAssignmentRS();

    file.close();
    return 0;
}