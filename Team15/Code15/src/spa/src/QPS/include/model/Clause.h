#include <set>
#include <string>
#include "../../../Utility.h"

#pragma once

class Clause {
private:
    ClauseType clauseType;
    std::set<std::string> synList;
public:
    Clause(ClauseType clauseType);
    void setSynList(std::set<std::string> synList);
    void addSyn(std::string syn);
    std::set<std::string> getSynList();
    ClauseType getType();
};