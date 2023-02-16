#include "QPS/include/evaluator/ClauseHandler.h"

ClauseHandler::ClauseHandler(PKB& pkb) {
    this->pkb = pkb;
}


void ClauseHandler::combineResult(ResultTable& resultTable, Result& result) {
    std::string firstArgName;
    std::string secondArgName;
    std::unordered_map<std::string, SynonymLinkageMap> firstArgValues;
    std::unordered_map<std::string, SynonymLinkageMap> secondArgValues;

    if (result.isFirstArgSynonym() && result.isSecondArgSynonym()) {
        firstArgName = result.getFirstArgName();
        secondArgName = result.getSecondArgName();
        firstArgValues = result.getFirstArgValue();
        secondArgValues = result.getSecondArgValue();
        combineTwoSynResult(firstArgName, firstArgValues, secondArgName, secondArgValues, resultTable);
    }
    else if (result.isFirstArgSynonym()) {
        firstArgName = result.getFirstArgName();
        firstArgValues = result.getFirstArgValue();
        combineOneSynResult(firstArgName, firstArgValues, resultTable);
    }
    else if (result.isSecondArgSynonym()) {
        secondArgName = result.getSecondArgName();
        secondArgValues = result.getSecondArgValue();
        combineOneSynResult(secondArgName, secondArgValues, resultTable);
    }
}

// TODO: Refactor code by creating more intermediate vars

void ClauseHandler::combineTwoSynResult(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynValues,
    std::string secondSynName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynValues, ResultTable& resultTable) {
    filterCurrResult(firstSynName, firstSynValues, secondSynName, secondSynValues, resultTable);
    filterResultTable(firstSynName, firstSynValues, resultTable);
    filterCurrResultLinkageSet(firstSynName, firstSynValues, secondSynName, secondSynValues, resultTable);
    filterResultTableLinkageSet(firstSynName, firstSynValues, secondSynName, resultTable);

    filterOneSynToResult(secondSynName, secondSynValues, firstSynName, resultTable);
    filterResultTable(secondSynName, secondSynValues, resultTable);
    filterOneSynLinkageSet(secondSynName, secondSynValues, firstSynName, resultTable);
    filterResultTableLinkageSet(secondSynName, secondSynValues, firstSynName, resultTable);
    
}

//first synonym is the synoym to combine, second is the linked synonym
void ClauseHandler::filterCurrResult(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynCurrValues,
    std::string secondSynName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynCurrValues, ResultTable& resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> firstSynTableValues = resultTable.getSynonymEntry(firstSynName);
    std::set<std::string> synValuesToRemove;
    for (auto firstSynCurrValue : firstSynCurrValues) {
        //can't find this synonym value in table, then delete it in current result
        if (firstSynTableValues.count(firstSynCurrValue.first) == 0) {
            //since only 2 args, first arg can only be linked to second arg
            //linkedSynValues is the set arg1 currValue keep indicating all the links of arg1 currValue with arg2
            std::set<std::string> linkedSynValues = firstSynCurrValue.second.getLinkedSynValueSet(secondSynName);
            for (auto linkedSynValue : linkedSynValues) {
                //for all the values, go to arg2 and delete the linkage
                secondSynCurrValues.at(linkedSynValue).deleteLinkage(firstSynName, firstSynCurrValue.first);
                //since arg2 can only be linked to arg1, if the value contains no linkage with arg1, we can delete this value safely.
                if (secondSynCurrValues.at(linkedSynValue).isEmptyLinkageSet(firstSynName)) {
                    secondSynCurrValues.erase(linkedSynValue);
                }
            }
            synValuesToRemove.insert(firstSynCurrValue.first);
        }
    }
    for (auto synValueToRemove : synValuesToRemove) {
        firstSynCurrValues.erase(synValueToRemove);
    }
}

void ClauseHandler::filterResultTable(std::string currSynName, std::unordered_map<std::string, SynonymLinkageMap>& currSynValues, ResultTable& resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> tableSynValues = resultTable.getSynonymEntry(currSynName);
    for (auto tableSynValue : tableSynValues) {
        //the entry can't be found in the current syn values, then delete the entry in table
        if (currSynValues.count(tableSynValue.first) == 0) {
            deleteSynTableEntry(currSynName, tableSynValue.first, resultTable);
        }
    }
}

void ClauseHandler::filterCurrResultLinkageSet(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynValues,
    std::string secondSynName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynValues, ResultTable& resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> firstSynTableResult = resultTable.getSynonymEntry(firstSynName);
    for (auto currSynValue = firstSynValues.begin(); currSynValue != firstSynValues.end(); currSynValue++) {
        SynonymLinkageMap& tableSynValueLinkageMap = resultTable.getSynonymEntry(firstSynName).at(currSynValue->first);
        SynonymLinkageMap& currSynValueLinkageMap = currSynValue->second;
        bool isTableFirstSecondSynLinked = !tableSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
        bool isCurrFirstSecondSynLinked = !currSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
        // if both table and current result contains the linkage set, find the intersection of them
        if (isTableFirstSecondSynLinked && isCurrFirstSecondSynLinked) {
            std::set<std::string> intersectedValues = Utility::getSetIntersection(
                currSynValue->second.getLinkageMap().at(secondSynName),
                tableSynValueLinkageMap.getLinkageMap().at(secondSynName));
            std::set<std::string> linkageToDelete;
            for (auto linkedValue : currSynValueLinkageMap.getLinkedSynValueSet(secondSynName)) {
                if (intersectedValues.count(linkedValue) == 0) {
                    linkageToDelete.insert(linkedValue);
                    //currSynValueLinkageMap.deleteLinkage(secondSynName, );
                    //currSynValueLinkageMap.getLinkageMap().at(secondSynName).erase(linkedValue);
                    secondSynValues.at(linkedValue).deleteLinkage(firstSynName, currSynValue->first);
                    //secondSynValues.at(linkedValue).getLinkageMap().find(firstSynName)->second.erase(currSynValue.first);
                    if (secondSynValues.at(linkedValue).isEmptyLinkageSet(firstSynName)) {
                        secondSynValues.erase(linkedValue);
                    }
                }
            }
            for (auto linkedValue : linkageToDelete) {
                currSynValueLinkageMap.deleteLinkage(secondSynName, linkedValue);
            }
        }
        else if (!isTableFirstSecondSynLinked && isCurrFirstSecondSynLinked) {
            tableSynValueLinkageMap.insertNewEntry(secondSynName, currSynValueLinkageMap.getLinkedSynValueSet(secondSynName));
        }
    }
}

void ClauseHandler::filterResultTableLinkageSet(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynValues,
    std::string secondSynName, ResultTable& resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap>& firstSynTableValues = resultTable.getSynonymEntry(firstSynName);
    
    for (auto tableSynValue = firstSynTableValues.begin(); tableSynValue != firstSynTableValues.end(); tableSynValue++) {
        SynonymLinkageMap& tableSynValueLinkageMap = tableSynValue->second;
        SynonymLinkageMap& currSynValueLinkageMap = firstSynValues.at(tableSynValue->first);
        bool isTableFirstSecondSynLinked = !tableSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
        bool isCurrFirstSecondSynLinked = !currSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
        if (isTableFirstSecondSynLinked && isCurrFirstSecondSynLinked) {
            std::set<std::string> intersectedValues = Utility::getSetIntersection(
                firstSynValues.at(tableSynValue->first).getLinkedSynValueSet(secondSynName)
                /*firstSynValues.find(tableSynValue.first)->second.getLinkageMap().find(secondSynName)->second*/,
                tableSynValueLinkageMap.getLinkedSynValueSet(secondSynName));
            std::set<std::string> linkedSynValues = tableSynValueLinkageMap.getLinkedSynValueSet(secondSynName);
            std::set<std::string> synsToDelete;
            for (auto linkedTableValue : linkedSynValues) {
                if (intersectedValues.count(linkedTableValue) == 0) {
                    deleteLinkage(secondSynName, linkedTableValue, firstSynName, tableSynValue->first, resultTable);
                    synsToDelete.insert(linkedTableValue);
                }
            }
            for (auto synToDelete : synsToDelete) {
                tableSynValueLinkageMap.deleteLinkage(secondSynName, synToDelete);
            }
        } // TODO: Decide if there's a "else" situation to handle here?
    }
}

void ClauseHandler::filterOneSynToResult(std::string currSynName, std::unordered_map<std::string, SynonymLinkageMap>& currSynValues, std::string linkedSynName, ResultTable& resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> tableSynValues = resultTable.getSynonymEntry(currSynName);
    std::set<std::string> synValuesToRemove;
    for (auto currSynValue : currSynValues) {
        //can't find entry in table
        if (tableSynValues.count(currSynValue.first) == 0) {
            //since only 2 argument, first arg can only be linked to second arg
            std::set<std::string> linkedSynValues = currSynValue.second.getLinkedSynValueSet(linkedSynName);
            for (auto linkedSynValue : linkedSynValues) {
                SynonymLinkageMap& tableLinkedSynMap = resultTable.getSynonymEntry(linkedSynName).at(linkedSynValue);
                tableLinkedSynMap.deleteLinkage(currSynName, currSynValue.first);
                    //getLinkageMap().find(currSynName)->second.erase(currSynValue.first);
                if (tableLinkedSynMap.isEmptyLinkageSet(currSynName)) {
                    resultTable.getSynonymEntry(linkedSynName).erase(linkedSynValue);
                }
            }
            synValuesToRemove.insert(currSynValue.first);
        }
    }
    for (auto synValueToRemove : synValuesToRemove) {
        currSynValues.erase(synValueToRemove);
    }
}

void ClauseHandler::filterOneSynLinkageSet(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynValues, 
    std::string secondSynName, ResultTable &resultTable) {
    std::unordered_map<std::string, SynonymLinkageMap> tableFirstSynValues = resultTable.getSynonymEntry(firstSynName);

    for (auto currSynValue = firstSynValues.begin(); currSynValue != firstSynValues.end(); currSynValue++) {
        SynonymLinkageMap& tableSynValueLinkageMap = resultTable.getSynonymEntry(firstSynName).at(currSynValue->first);
        SynonymLinkageMap& currSynValueLinkageMap = currSynValue->second;
        bool isTableFirstSecondSynLinked = !tableSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
        bool isCurrFirstSecondSynLinked = !currSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
        if (isTableFirstSecondSynLinked && isCurrFirstSecondSynLinked) {
            std::set<std::string> intersectedValues = Utility::getSetIntersection(
                currSynValueLinkageMap.getLinkedSynValueSet(secondSynName),
                tableSynValueLinkageMap.getLinkedSynValueSet(secondSynName));
            for (auto linkedSynValue : currSynValueLinkageMap.getLinkedSynValueSet(secondSynName)) {
                if (intersectedValues.count(linkedSynValue) == 0) {
                    currSynValueLinkageMap.deleteLinkage(secondSynName, linkedSynValue);
                        //.getLinkageMap().find(secondSynName)->second.erase(linkedSynValue);
                    //now we are merging arg2 into resultTable, since arg2 contains linkage with arg1 and arg1 is now merged into resultTable, 
                    //after deleting the link in arg2, we need to go through the resultTable and delete the link there.
                    resultTable.getSynonymEntry(secondSynName).at(linkedSynValue).deleteLinkage(firstSynName, currSynValue->first);
                        //getLinkageMap().find(firstSynName)->second.erase(currSynValue.first);
                    if (resultTable.getSynonymEntry(secondSynName).at(linkedSynValue).isEmptyLinkageSet(firstSynName)) {
                        resultTable.getSynonymEntry(secondSynName).erase(linkedSynValue);
                    }
                }
            }
        }
        else if (!isTableFirstSecondSynLinked && isCurrFirstSecondSynLinked) {
            tableSynValueLinkageMap.insertNewEntry(secondSynName, currSynValueLinkageMap.getLinkedSynValueSet(secondSynName));

        }
    }
}

void ClauseHandler::combineOneSynResult(std::string currSynName, std::unordered_map<std::string, SynonymLinkageMap>& currSynValues, ResultTable& resultTable) {
    if (resultTable.isSynonymPresent(currSynName)) {
        std::unordered_map<std::string, SynonymLinkageMap> tableSynValues = resultTable.getSynonymEntry(currSynName);
        for (auto tableSynValue : tableSynValues) {
            if (currSynValues.count(tableSynValue.first) == 0) {
                deleteSynTableEntry(currSynName, tableSynValue.first, resultTable);
            }
        }
        //mergeResultToTable(synonymName, synonymInstanceCollection, resultTable);
    }
    else {
        resultTable.insertSynonymEntry(currSynName, currSynValues);
    }
}

void ClauseHandler::deleteSynTableEntry(std::string synName, std::string synValue, ResultTable& resultTable) {
    std::unordered_map<std::string, std::set<std::string>> tableLinkageMap = resultTable.getSynonymEntry(synName).at(synValue).getLinkageMap();
    
    //example: "11":{"stmt2":[12,13,14],"stmt3":[10,11,12]} iterate through all linked instance and delete them, then delete the synonym instance entry
    for (pair<std::string, std::set<std::string>> linkedInstanceCollection : tableLinkageMap) {
        for (std::string linkedValue : linkedInstanceCollection.second) {
            deleteLinkage(linkedInstanceCollection.first, linkedValue, synName, synValue, resultTable);
        }
    }
    resultTable.deleteSynonymInstance(synName, synValue);
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

