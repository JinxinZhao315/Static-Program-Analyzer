#pragma once

#include "stdio.h"
#include "string"
#include <iostream>
#include <vector>
#include <utility>
#include "../parser/Line.h"

using namespace std;

pair<vector<string>, vector<string>> getLHSandRHSofAssignStatement(vector<string> tokens);
string getVarNameFromReadStatement(vector<string> tokens);