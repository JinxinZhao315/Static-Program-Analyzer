#include <vector>
#include <string>
#include "Clause.h"
#pragma once

class ClauseEvalGroup {
private:
    std::vector<Clause*> clauseList;
    std::vector<std::string> synList;
public:
    ClauseEvalGroup();
    ClauseEvalGroup(std::vector<Clause*> clauseList);
    void fillSynList();
    void addClause(Clause* clause);
    std::vector<Clause*> getClauseList();
    std::vector<std::string> getSynList();
};