#pragma once
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>

void processFile(std::ifstream &file);
void generateFollowsRS();
void generateNestingLevel();
bool findToken(std::string s);
bool emptyToken(std::string token);
std::vector<std::string> pushToken(std::vector<std::string> tokens, std::string token);
std::vector<std::string> tokenise(std::string line);
