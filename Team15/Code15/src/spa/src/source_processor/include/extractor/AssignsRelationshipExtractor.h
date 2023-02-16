#pragma once

#include "Extractor.h"

int precedence(string c);
bool isOperator(string c);
bool isNumber(string num);
vector<string> convertToPostfix(vector<string> tokens, const set<string>& variables);
unordered_map<string, set<Line> > extractAssignmentRS(const vector<Line>& program, const set<string>& variables);