#pragma once

#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <algorithm>

using namespace std;

class StatementParser {
public:
    StatementParser() = default;

    virtual void parse() = 0;
    virtual void validateSyntax() = 0;

}