//
// Created by Jinxin Zhao on 3/2/23.
//

#include "ClauseHandler.h"

ClauseHandler::ClauseHandler(PKB& pkb) {
    this->pkb = pkb;
}

void ClauseHandler::combineResult(ResultTable& resultTable, Result& result) {

    std::string synonymName;
    std::set<std::string> synonymSet;

    std::set<std::string> intersection;
    std::insert_iterator<std::set<std::string>> intersectIterate(intersection, intersection.begin());


    if (result.isLeftArgSynonym()) {
        synonymName = result.getLeftArgName();
        synonymSet = result.getLeftArgValue();
    }
    else {
        synonymName = result.getRighttArgName();
        synonymSet = result.getRightArgValue();
    }
    if (resultTable.isKeyPresent(synonymName)) {
        std::set<std::string> currSynonymValue = resultTable.getValueFromKey(synonymName);
        set_intersection(synonymSet.begin(), synonymSet.end(), currSynonymValue.begin(), currSynonymValue.end(), intersectIterate);
        resultTable.insertKeyValuePair(synonymName, intersection);
    }
    else {
        resultTable.insertKeyValuePair(synonymName, synonymSet);
    }
}
