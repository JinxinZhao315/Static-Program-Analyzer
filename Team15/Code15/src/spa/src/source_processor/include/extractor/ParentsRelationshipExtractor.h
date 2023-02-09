#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>
#include <stdio.h>
#include <iostream>
#include "../parser/Line.h"

using namespace std;

bool endsWith(const vector<string>& vec, const string& str);
pair<map<int, int>, map<int, set<int> > > generateParentsRelationship(const vector<Line>& program);