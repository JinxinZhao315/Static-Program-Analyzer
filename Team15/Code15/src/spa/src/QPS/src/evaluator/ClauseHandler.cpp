#include "QPS/include/evaluator/ClauseHandler.h"

ClauseHandler::ClauseHandler(PKB& pkb) {
    this->pkb = pkb;
}


void ClauseHandler::combineResult(ResultTable& resultTable, Result& result) {
    std::unordered_map<std::string, SynonymLinkageMap> firstValues;
    std::unordered_map<std::string, SynonymLinkageMap> secondValues;

    if (result.isFirstArgSynonym() && result.isSecondArgSynonym()) {
        firstValues = result.getFirstArgValue();
        secondValues = result.getSecondArgValue();
        combineTwoSynResult(result.getFirstArgName(), firstValues, result.getSecondArgName(), secondValues, resultTable);
    }
    else if (result.isFirstArgSynonym()) {
        //std::unordered_map<std::string, SynonymLinkageMap> firstArgVal = result.getFirstArgValue();
        firstValues = result.getFirstArgValue();
        combineOneSynResult(result.getFirstArgName(), firstValues, resultTable);
    }
    else if (result.isSecondArgSynonym()) {
        secondValues = result.getSecondArgValue();
        combineOneSynResult(result.getSecondArgName(), secondValues, resultTable);
    } 
}

//void ClauseHandler::combine(std::string synonymName, std::set<std::string>& synonymSet, ResultTable& resultTable) {
//    std::set<std::string> intersection;
//    std::insert_iterator<std::set<std::string>> intersectIterate(intersection, intersection.begin());
//    if (resultTable.isKeyPresent(synonymName)) {
//       
//        std::set<std::string> currSynonymValue = resultTable.getValueFromKey(synonymName);
//        set_intersection(synonymSet.begin(), synonymSet.end(), currSynonymValue.begin(), currSynonymValue.end(), intersectIterate);
//        resultTable.deleteKeyValuePair(synonymName);
//        resultTable.insertKeyValuePair(synonymName, intersection);      
//    }
//    else {
//        resultTable.insertKeyValuePair(synonymName, synonymSet);
//    }
//}

void ClauseHandler::combineTwoSynResult(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult,
    std::string secondSynName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynResult, ResultTable& resultTable) {
    if (!resultTable.isSynonymPresent(firstSynName)) {
        resultTable.insertSynonymEntry(firstSynName, firstSynResult);
        combineOneSynResult(secondSynName, secondSynResult, resultTable);
    }
    else if (!resultTable.isSynonymPresent(secondSynName)) {
        resultTable.insertSynonymEntry(secondSynName, secondSynResult);
        combineOneSynResult(firstSynName, firstSynResult, resultTable);
    }
    else {
        filterCurrResult(firstSynName, firstSynResult, secondSynName, secondSynResult, resultTable);
        filterResultTable(firstSynName, firstSynResult, resultTable);
        filterCurrResultLinkageSet(firstSynName, firstSynResult, secondSynName, secondSynResult, resultTable);
        filterResultTableLinkageSet(firstSynName, firstSynResult, secondSynName, resultTable);
        
        filterOneSynToResult(secondSynName, secondSynResult, firstSynName , resultTable);
        filterResultTable(secondSynName, secondSynResult, resultTable);
        filterOneSynLinkageSet(firstSynName, firstSynResult, secondSynName, resultTable);
        filterResultTableLinkageSet(firstSynName, firstSynResult, secondSynName, resultTable);
    }
}

void ClauseHandler::filterOneSynToResult(std::string synName, std::unordered_map<std::string, SynonymLinkageMap>& synValue, std::string linkedSynName, ResultTable& resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> synTableResult = resultTable.getSynonymEntry(synName);
    std::set<std::string> keysToRemove;
    for (auto currSynonymInstance : synValue) {
        //can't find entry in table
        if (synTableResult.find(currSynonymInstance.first) == synTableResult.end()) {
            //since only 2 argument, first arg can only be linked to second arg
            std::set<std::string> linkedSynInstances = currSynonymInstance.second.getLinkageMap().find(linkedSynName)->second;
            for (auto linkedSynInstance : linkedSynInstances) {
                resultTable.getSynonymEntry(linkedSynName).find(linkedSynInstance)->second.getLinkageMap().find(synName)->second.erase(currSynonymInstance.first);
                if (resultTable.getSynonymEntry(linkedSynName).find(linkedSynInstance)->second.isEmptyLinkageSet(synName)) {
                    resultTable.getSynonymEntry(linkedSynName).erase(linkedSynInstance);
                }
            }
            keysToRemove.insert(currSynonymInstance.first);
        }
    }
    for (auto keyToRemove : keysToRemove) {
        synValue.erase(keyToRemove);
    }
}

void ClauseHandler::filterOneSynLinkageSet(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult, 
    std::string secondSynName, ResultTable &resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> firstSynTableResult = resultTable.getSynonymEntry(firstSynName);

    for (auto currSynonymInstance : firstSynResult) {
        if (!resultTable.getSynonymEntry(firstSynName).find(currSynonymInstance.first)->second.isEmptyLinkageSet(secondSynName)
            && !currSynonymInstance.second.isEmptyLinkageSet(secondSynName)) {
            std::set<std::string> intersectedInstances = Utility::getSetIntersection(
                currSynonymInstance.second.getLinkageMap().find(secondSynName)->second,
                resultTable.getSynonymEntry(firstSynName).find(currSynonymInstance.first)->second.getLinkageMap().find(secondSynName)->second);
            for (auto linkedInstance : currSynonymInstance.second.getLinkageMap().find(secondSynName)->second) {
                if (intersectedInstances.count(linkedInstance) == 0) {
                    firstSynResult.find(currSynonymInstance.first)->second.getLinkageMap().find(secondSynName)->second.erase(linkedInstance);
                    resultTable.getSynonymEntry(secondSynName).find(linkedInstance)->second.getLinkageMap().find(firstSynName)->second.erase(currSynonymInstance.first);
                    if (resultTable.getSynonymEntry(secondSynName).find(linkedInstance)->second.isEmptyLinkageSet(firstSynName)) {
                        resultTable.getSynonymEntry(secondSynName).erase(linkedInstance);
                    }
                }
            }
        }
        else if (resultTable.getSynonymEntry(firstSynName).at(currSynonymInstance.first).isEmptyLinkageSet(secondSynName)
            && !currSynonymInstance.second.isEmptyLinkageSet(secondSynName)) {
            resultTable.getSynonymEntry(firstSynName).at(currSynonymInstance.first).getLinkageMap().insert({ secondSynName, currSynonymInstance.second.getLinkageMap().at(secondSynName) });

        }
    }
}

//first synonym is the synoym to combine, second is the linked synonym
void ClauseHandler::filterCurrResult(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynonymValue,
    std::string secondSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynonymValue, ResultTable& resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> firstSynTableResult = resultTable.getSynonymEntry(firstSynonymName);
    std::set<std::string> keysToRemove;
    for (auto currSynonymInstance : firstSynonymValue) {
        //can't find entry in table
        if (firstSynTableResult.find(currSynonymInstance.first) == firstSynTableResult.end()) {
            //since only 2 argument, first arg can only be linked to second arg
            std::set<std::string> linkedSynInstances = currSynonymInstance.second.getLinkageMap().find(secondSynonymName)->second;
            for (auto linkedSynInstance : linkedSynInstances) {
                secondSynonymValue.find(linkedSynInstance)->second.getLinkageMap().find(firstSynonymName)->second.erase(currSynonymInstance.first);
                if (secondSynonymValue.find(linkedSynInstance)->second.isEmptyLinkageSet(firstSynonymName)) {
                    secondSynonymValue.erase(linkedSynInstance);
                }
            }
            keysToRemove.insert(currSynonymInstance.first);
        }
    }
    for (auto keyToRemove : keysToRemove) {
        firstSynonymValue.erase(keyToRemove);
    }
}

void ClauseHandler::filterResultTable(std::string synName, std::unordered_map<std::string, SynonymLinkageMap>& synValue, ResultTable &resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> tableSynValue = resultTable.getSynonymEntry(synName);
    for (auto tableSynonymInstance : tableSynValue) {
        if (synValue.find(tableSynonymInstance.first) == synValue.end()) {
            deleteSynTableEntry(synName, tableSynonymInstance.first, resultTable);
        }
    }
}

void ClauseHandler::filterCurrResultLinkageSet(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult, 
    std::string secondSynName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynResult, ResultTable &resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> firstSynTableResult = resultTable.getSynonymEntry(firstSynName);
    
    for (auto currSynonymInstance : firstSynResult) {
        if (!resultTable.getSynonymEntry(firstSynName).find(currSynonymInstance.first)->second.isEmptyLinkageSet(secondSynName)
            && !currSynonymInstance.second.isEmptyLinkageSet(secondSynName)) {
            std::set<std::string> intersectedInstances = Utility::getSetIntersection(
                currSynonymInstance.second.getLinkageMap().find(secondSynName)->second,
                resultTable.getSynonymEntry(firstSynName).find(currSynonymInstance.first)->second.getLinkageMap().find(secondSynName)->second);
            for (auto linkedInstance : currSynonymInstance.second.getLinkageMap().find(secondSynName)->second) {
                if (intersectedInstances.count(linkedInstance) == 0) {
                    firstSynResult.find(currSynonymInstance.first)->second.getLinkageMap().find(secondSynName)->second.erase(linkedInstance);
                    secondSynResult.find(linkedInstance)->second.getLinkageMap().find(firstSynName)->second.erase(currSynonymInstance.first);
                    if (secondSynResult.find(linkedInstance)->second.isEmptyLinkageSet(firstSynName)) {
                        secondSynResult.erase(linkedInstance);
                    }
                }
            }
        }
        //table is enmpty but currResult is not
        else if(resultTable.getSynonymEntry(firstSynName).at(currSynonymInstance.first).isEmptyLinkageSet(secondSynName)
            && !currSynonymInstance.second.isEmptyLinkageSet(secondSynName)){
            resultTable.getSynonymEntry(firstSynName).at(currSynonymInstance.first).getLinkageMap().insert({ secondSynName, currSynonymInstance.second.getLinkageMap().at(secondSynName) });

        }
    }
}

void ClauseHandler::filterResultTableLinkageSet(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult,
    std::string secondSynonymName, ResultTable &resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> firstSynTableResult = resultTable.getSynonymEntry(firstSynonymName);
    for (auto synonymInstance : firstSynTableResult) {
        if (!resultTable.getSynonymEntry(firstSynonymName).find(synonymInstance.first)->second.isEmptyLinkageSet(secondSynonymName)
            && !firstSynResult.find(synonymInstance.first)->second.isEmptyLinkageSet(secondSynonymName)) {
            std::set<std::string> intersectedInstances = Utility::getSetIntersection(
                firstSynResult.find(synonymInstance.first)->second.getLinkageMap().find(secondSynonymName)->second,
                resultTable.getSynonymEntry(firstSynonymName).find(synonymInstance.first)->second.getLinkageMap().find(secondSynonymName)->second);
            std::set<std::string> linkedSynSet = resultTable.getSynonymEntry(firstSynonymName).find(synonymInstance.first)->second.getLinkageMap().find(secondSynonymName)->second;
            std::set<std::string> synToDeleteSet;
            for (auto linkedTableInstance : linkedSynSet) {
                if (intersectedInstances.count(linkedTableInstance) == 0) {
                    deleteLinkage(secondSynonymName, linkedTableInstance, firstSynonymName, synonymInstance.first, resultTable);
                    synToDeleteSet.insert(linkedTableInstance);
                }
            }
            for (auto synToDelete : synToDeleteSet) {
                resultTable.getSynonymEntry(firstSynonymName).find(synonymInstance.first)->second.getLinkageMap().find(secondSynonymName)->second.erase(synToDelete);
            }
        }
    }
}

void ClauseHandler::combineOneSynResult(std::string synonymName, std::unordered_map<std::string, SynonymLinkageMap>& currSynonymValues, ResultTable& resultTable) {
    if (resultTable.isSynonymPresent(synonymName)) {
        std::unordered_map<std::string, SynonymLinkageMap> tableSynonymValues = resultTable.getSynonymEntry(synonymName);
        for (auto key : tableSynonymValues) {
            if (currSynonymValues.find(key.first) == currSynonymValues.end()) {
                deleteSynTableEntry(synonymName, key.first, resultTable);
            }
        }
        //mergeResultToTable(synonymName, synonymInstanceCollection, resultTable);
    }
    else {
        resultTable.insertSynonymEntry(synonymName, currSynonymValues);
    }
}


//void ClauseHandler::mergeResultToTable(std::string synonymName, std::unordered_map<std::string, SynonymLinkageMap>& currResult, ResultTable& resultTable) {
//    std::unordered_map<std::string, SynonymLinkageMap> synonymEntry = resultTable.getSynonymEntry(synonymName);
//    for (auto tableSynonymInstance = synonymEntry.begin(); tableSynonymInstance != synonymEntry.end(); tableSynonymInstance++) {
//        std::unordered_map<std::string, std::set<std::string>> currLinkageMap = currResult.find(tableSynonymInstance->first)->second.getLinkageMap();
//        for (auto currResultLinkage = currLinkageMap.begin(); currResultLinkage != currLinkageMap.end(); currResultLinkage++) {
//            //currResultLinkage example: "s2":{"6","7","8"}
//            //tableSynonymInstance example: "5":{"s2":{"6","7","8"}}
//            tableSynonymInstance->second.insertLinkage(currResultLinkage->first, currResultLinkage->second);
//            if (tableSynonymInstance->second.isEmptyLinkageSet(currResultLinkage->first) {
//                deleteSynTableEntry(linkedSynonym, linkedSynonymInstance, resultTable); 
//            }
//        }
//    }
//}

void ClauseHandler::deleteSynTableEntry(std::string synName, std::string synInstance, ResultTable& resultTable) {
    std::unordered_map<std::string, std::set<std::string>> linkageMap = resultTable.getSynonymEntry(synName).find(synInstance)->second.getLinkageMap();
    
    //example: "11":{"stmt2":[12,13,14],"stmt3":[10,11,12]} iterate through all linked instance and delete them, then delete the synonym instance entry
    for (pair<std::string, std::set<std::string>> linkedInstanceCollection : linkageMap) {
        for (std::string linkedInstance : linkedInstanceCollection.second) {
            deleteLinkage(linkedInstanceCollection.first, linkedInstance, synName, synInstance, resultTable);
        }
    }
    resultTable.deleteSynonymInstance(synName, synInstance);
}

void ClauseHandler::deleteLinkage(std::string linkedSynName, std::string linkedSynInstance, 
    std::string synName, std::string synInstance, ResultTable& resultTable) {
    resultTable.getSynonymEntry(linkedSynName).find(linkedSynInstance)->second.deleteLinkage(synName, synInstance);

    //example: "stmt2":{"6":{"stmt1": [5], "stmt2": [7]}}}, now delete 5, "stmt1" entry becomes empty, then "6" can't be selected now
    if (resultTable.getSynonymEntry(linkedSynName).find(linkedSynInstance)->second.isEmptyLinkageSet(synName)) {
        deleteSynTableEntry(linkedSynName, linkedSynInstance, resultTable);
    }
}

std::set<std::string> ClauseHandler::getResultFromPKB(PKB& pkb, string DeType) {
    std::set<std::string> ret;
    if (DeType == "constant") {
        ret = pkb.getAllConstVals();
    }
    else if (DeType == "procedure") {
        ret = pkb.getAllProcNames();
    }
    else if (DeType == "variable") {
        ret = pkb.getAllVarNames();
    }
    else if (DeType == "stmt") {
        std::set<int> allStmtIntSet = pkb.getAllStmtNums();
        for (int stmtNum: allStmtIntSet) {
            ret.insert(to_string(stmtNum));
        }
    } else  {
        Tokens::Keyword DeToken;
        if (DeType == "read") {
            DeToken = Tokens::Keyword::READ;
        } else if (DeType == "print") {
            DeToken = Tokens::Keyword::PRINT;
        } else if (DeType == "assign") {
            DeToken = Tokens::Keyword::ASSIGN;
        } else if (DeType == "call") {
            DeToken = Tokens::Keyword::CALL;
        } else if (DeType == "while") {
            DeToken = Tokens::Keyword::WHILE;
        } else if (DeType == "if") {
            DeToken = Tokens::Keyword::IF;
        } else {
            throw runtime_error("unsupported DeType in ClauseHandler" + DeType);
        }

        std::set<int> allStmtIntSet = pkb.getAllStmtNumsByType(DeToken);
        for (int stmtNum: allStmtIntSet) {
            ret.insert(to_string(stmtNum));
        }
    }
    return ret;
}

void ClauseHandler::resultTableCheckAndAdd(string synonymName, ResultTable& resultTable, string DeType) {
    if (!resultTable.isSynonymPresent(synonymName)) {
        Result result;
        std::set<string> synonymInstanceStrSet = getResultFromPKB(pkb, DeType);
        std::unordered_map<std::string, SynonymLinkageMap> synonymInstanceCollection;
        for (std::string key : synonymInstanceStrSet) {
            synonymInstanceCollection.insert(std::make_pair<>(key, SynonymLinkageMap()));
        }
        result.setFirstArg(synonymName, synonymInstanceCollection);
        ClauseHandler::combineResult(resultTable, result);
    }
}

