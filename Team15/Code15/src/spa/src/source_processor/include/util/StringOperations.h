#pragma once

#include "stdio.h"
#include "string"
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include "../parser/Line.h"

using namespace std;

pair<vector<string>, vector<string>> getLHSandRHSofAssignStatement(vector<string> tokens);
string getVarNameFromReadStatement(vector<string> tokens);
string getVarNameFromPrintStatement(vector<string> tokens);
string getSecondToken(vector<string> tokens);
set<string> getVariablesFromStatement(vector<string> tokens, const set<string>& variables);
