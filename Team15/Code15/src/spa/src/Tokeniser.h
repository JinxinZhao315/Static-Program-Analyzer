#pragma once
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stdio.h>

using namespace std;

void driver();
map<int, vector<string>> processFile(std::ifstream &file);
map<int, int> generateFollowsRS(map<int, int> nesting_level);
map<int, set<int>> generateFollowsStarRS(map<int, int> nesting_level);
map<int, int> generateNestingLevel(map<int, vector<string>>);
map<string, vector<vector<string>>> generateAssignmentRS(map<int, vector<string>>);
int precedence(std::string c);
bool isOperator(std::string c);
bool isNumber(std::string num);
std::vector<std::string> convertToPostfix(std::vector<std::string> tokens, int startIndex);
bool findToken(std::string s);
bool emptyToken(std::string token);
std::vector<std::string> pushToken(std::vector<std::string> tokens, std::string token);
std::vector<std::string> tokenise(std::string line);