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

void ClauseHandler::combineTwoSynResult(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult,
    std::string secondSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynResult, ResultTable& resultTable) {
    if (!resultTable.isSynonymPresent(firstSynonymName)) {
        resultTable.insertSynonymEntry(firstSynonymName, firstSynResult);
        combineOneSynResult(secondSynonymName, secondSynResult, resultTable);
    }
    else if (!resultTable.isSynonymPresent(secondSynonymName)) {
        resultTable.insertSynonymEntry(secondSynonymName, secondSynResult);
        combineOneSynResult(firstSynonymName, firstSynResult, resultTable);
    }
    else {
        std::unordered_map<std::string, SynonymLinkageMap> firstSynTableResult = resultTable.getSynonymEntry(firstSynonymName);
        for (auto key : firstSynResult) {
            if (firstSynTableResult.find(key.first) == firstSynTableResult.end()) {
                std::set<std::string> linkedSecondSynInstances = key.second.getLinkageMap().find(secondSynonymName)->second;
                for (auto linkedSecondSynInstance : linkedSecondSynInstances) {
                    secondSynResult.find(linkedSecondSynInstance)->second.getLinkageMap().find(firstSynonymName)->second.erase(key.first);
                }
                firstSynResult.erase(key.first);
            }
        }
        for (auto key : firstSynTableResult) {
            if (firstSynResult.find(key.first) == firstSynResult.end()) {
                deleteSynTableEntry(firstSynonymName, key.first, resultTable);
            }
        }
        mergeResultToTable(firstSynonymName, firstSynResult, resultTable);


        std::unordered_map<std::string, SynonymLinkageMap> secondSynTableResult = resultTable.getSynonymEntry(secondSynonymName);
        for (auto key : secondSynResult) {
            if (secondSynTableResult.find(key.first) == secondSynTableResult.end()) {
                std::set<std::string> linkedFirstSynInstances = key.second.getLinkageMap().find(firstSynonymName)->second;
                for (auto linkedFirstSynInstance : linkedFirstSynInstances) {
                    firstSynResult.find(linkedFirstSynInstance)->second.getLinkageMap().find(secondSynonymName)->second.erase(key.first);
                }
                secondSynResult.erase(key.first);
            }
        }
        for (auto key : secondSynTableResult) {
            if (secondSynResult.find(key.first) == secondSynResult.end()) {
                deleteSynTableEntry(secondSynonymName, key.first, resultTable);
            }
        }
        mergeResultToTable(secondSynonymName, secondSynResult, resultTable);
    }
}

void ClauseHandler::combineOneSynResult(std::string synonymName, std::unordered_map<std::string, SynonymLinkageMap>& synonymInstanceCollection, ResultTable& resultTable) {
    if (resultTable.isSynonymPresent(synonymName)) {
        std::unordered_map<std::string, SynonymLinkageMap> synonymValues = resultTable.getSynonymEntry(synonymName);
        //clear entry in currResult that doesn't appear in tableResult
        for (auto key : synonymInstanceCollection) {
            if (synonymValues.find(key.first) == synonymValues.end()) {
                //because one syn, can just erase
                synonymInstanceCollection.erase(key.first);
            }
        }
        //clear entry in tableResult that doesn't appear in currResult
        for (auto key : synonymValues) {
            if (synonymInstanceCollection.find(key.first) == synonymInstanceCollection.end()) {
                deleteSynTableEntry(synonymName, key.first, resultTable);
            }
        }
        mergeResultToTable(synonymName, synonymInstanceCollection, resultTable);
    }
    else {
        resultTable.insertSynonymEntry(synonymName, synonymInstanceCollection);
    }
}


void ClauseHandler::mergeResultToTable(std::string synonymName, std::unordered_map<std::string, SynonymLinkageMap>& currResult, ResultTable& resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> synonymEntry = resultTable.getSynonymEntry(synonymName);
    for (auto tableSynonymInstance : synonymEntry) {
        for (auto currResultLinkage : currResult.find(tableSynonymInstance.first)->second.getLinkageMap()) {
            if (tableSynonymInstance.second.getLinkageMap().find(currResultLinkage.first) == tableSynonymInstance.second.getLinkageMap().end()) {
                tableSynonymInstance.second.getLinkageMap().insert(currResultLinkage);
            }
            else {
                for (auto linkedSynInstance : currResultLinkage.second) {
                    tableSynonymInstance.second.getLinkageMap().find(currResultLinkage.first)->second.insert(linkedSynInstance);
                }
            }
        }
    }
}

void ClauseHandler::deleteSynTableEntry(std::string synonymName, std::string synonymInstance, ResultTable& resultTable) {
    std::unordered_map<std::string, std::set<std::string>> linkageMap = resultTable.getSynonymEntry(synonymName).find(synonymInstance)->second.getLinkageMap();
    
    for (auto linkedSynonymKey : linkageMap) {
        for (auto linkedSynonymInstance : linkedSynonymKey.second) {
            deleteLinkage(linkedSynonymKey.first, linkedSynonymInstance, synonymName, synonymInstance, resultTable);
        }
    }
}

void ClauseHandler::deleteLinkage(std::string linkedSynonym, std::string linkedSynonymInstance, 
    std::string synonymName, std::string synonymInstance, ResultTable& resultTable) {
    resultTable.getSynonymEntry(linkedSynonym).find(linkedSynonymInstance)->second.deleteLinkage(synonymName, synonymInstance);
    if (resultTable.getSynonymEntry(linkedSynonym).find(linkedSynonymInstance)->second.isEmptyLinkageSet(synonymName)) {
        deleteSynTableEntry(linkedSynonym, linkedSynonymInstance, resultTable);
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

//template <typename T>
//std::set<T> ClauseHandler::convertVecToSet(std::vector<T> vec) {
//    std::set<T> resultSet;
//    for (T t : vec) {
//        resultSet.insert(t);
//    }
//    return resultSet;
//}

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

