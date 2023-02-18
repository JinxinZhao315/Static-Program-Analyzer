#pragma once

#include <cstdio>
#include "string"
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <stack>
#include <regex>
#include "common/include/models/Line.h"

using namespace std;

pair<vector<string>, vector<string>> getLHSandRHSofAssignStatement(vector<string> tokens);
string getVarNameFromReadStatement(vector<string> tokens);
string getVarNameFromPrintStatement(vector<string> tokens);
string getSecondToken(vector<string> tokens);
set<string> getVariablesFromStatement(vector<string> tokens, const set<string>& variables);
int precedence(const string& c);
bool isOperator(string c);
bool isNumber(const string& num);
vector<string> convertToPostfix(const vector<string>& tokens, const set<string>& variables);
