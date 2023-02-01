#pragma once
#include <fstream>

void processFile(std::ifstream &file);
void generateNestingLevel();
void generateFollowsRS();
std::vector<std::string> tokenise(std::string line);