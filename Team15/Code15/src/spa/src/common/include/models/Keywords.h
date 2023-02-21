#pragma once

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Keywords {
public:
    Keywords();
    vector<string>* getKeywords();
    bool isKeyword(string token);
private:
    vector<string>* keywords;
};