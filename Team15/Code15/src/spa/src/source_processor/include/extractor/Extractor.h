#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>
#include <stdio.h>
#include <iostream>
#include "../parser/Line.h"
#include "FollowsRelationshipExtractor.h"
#include "ParentsRelationshipExtractor.h"

using namespace std;

class Extractor {
public:
    Extractor() {}
    void extract(const vector<Line>& program);

private:
    map<int, int> nestingLevel;
    map<int, int> followsRS;
    map<int, int> parentsRS;

    map<int, set<int> > followsStar;
    map<int, set<int> > parentsStar;
};
