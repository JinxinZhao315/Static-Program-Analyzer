#include <set>
#include <string>
#include "common/include/utils/Utility.h"

#pragma once

class Clause {
private:
    ClauseType clauseType;
    std::vector<std::string> synList;
public:
    Clause(ClauseType clauseType);
    void setSynList(std::vector<std::string> synList);
    void addSyn(std::string syn);
    std::vector<std::string> getSynList();
    ClauseType getType();
};