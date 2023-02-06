#pragma once
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>

void processFile(std::ifstream &file);
void generateFollowsRS();
void generateNestingLevel();
void generateAssignmentRS();
void addFollowsStarRelationship(int line_number, int follower_line_number);
int precedence(std::string c);
int isOperator(std::string c);
bool isNumber(std::string num) {
std::vector<std::string> convertToPostfix(std::vector<std::string> tokens, int startIndex);
bool findToken(std::string s);
bool emptyToken(std::string token);
std::vector<std::string> pushToken(std::vector<std::string> tokens, std::string token);
std::vector<std::string> tokenise(std::string line);
