#include "../../include/model/ClauseEvalGroup.h"

ClauseEvalGroup::ClauseEvalGroup() {

}

ClauseEvalGroup::ClauseEvalGroup(std::vector<Clause*> clauseList) {
    this->clauseList = clauseList;
    fillSynList();
}

void ClauseEvalGroup::fillSynList() {
    synList.clear();
    for (Clause* c : clauseList) {
        std::vector<std::string> tempSynList = c->getSynList();
        synList.insert(std::end(synList), std::begin(tempSynList), std::end(tempSynList));
        //synList.insert(tempSynList.begin(), tempSynList.end());
    }
}

void ClauseEvalGroup::addClause(Clause* clause) {
    clauseList.push_back(clause);
    std::vector<std::string> tempSynList = clause->getSynList();
    synList.insert(std::end(synList), std::begin(tempSynList), std::end(tempSynList));
}

std::vector<Clause*> ClauseEvalGroup::getClauseList() {
    return this->clauseList;
}

std::vector<std::string> ClauseEvalGroup::getSynList() {
    return this->synList;
}