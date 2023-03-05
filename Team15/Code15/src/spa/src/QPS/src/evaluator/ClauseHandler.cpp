#include "QPS/include/evaluator/ClauseHandler.h"

ClauseHandler::ClauseHandler(PKB& pkb) {
    this->pkb = pkb;
}


//void ClauseHandler::combineResult(ResultTable& resultTable, Result& result) {
//    std::string firstArgName;
//    std::string secondArgName;
//    std::unordered_map<std::string, SynonymLinkageMap> firstArgValues;
//    std::unordered_map<std::string, SynonymLinkageMap> secondArgValues;
//
//    if (result.isFirstArgSynonym() && result.isSecondArgSynonym()) {
//        firstArgName = result.getFirstArgName();
//        secondArgName = result.getSecondArgName();
//        firstArgValues = result.getFirstArgValue();
//        secondArgValues = result.getSecondArgValue();
//        combineTwoSynResult(firstArgName, firstArgValues, secondArgName, secondArgValues, resultTable);
//    }
//    else if (result.isFirstArgSynonym()) {
//        firstArgName = result.getFirstArgName();
//        firstArgValues = result.getFirstArgValue();
//        combineOneSynResult(firstArgName, firstArgValues, resultTable);
//    }
//    else if (result.isSecondArgSynonym()) {
//        secondArgName = result.getSecondArgName();
//        secondArgValues = result.getSecondArgValue();
//        combineOneSynResult(secondArgName, secondArgValues, resultTable);
//    }
//}
//
//// TODO: Refactor code by creating more intermediate vars
//
//void ClauseHandler::combineTwoSynResult(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynValues,
//    std::string secondSynName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynValues, ResultTable& resultTable) {
//    filterCurrResult(firstSynName, firstSynValues, secondSynName, secondSynValues, resultTable);
//    filterResultTable(firstSynName, firstSynValues, resultTable);
//    filterCurrResultLinkageSet(firstSynName, firstSynValues, secondSynName, secondSynValues, resultTable);
//    filterResultTableLinkageSet(firstSynName, firstSynValues, secondSynName, resultTable);
//
//    //filterOneSynWithLinkage(secondSynName, secondSynValues, firstSynName, resultTable);
//    filterResultTable(secondSynName, secondSynValues, resultTable);
//    //filterOneSynLinkageSet(secondSynName, secondSynValues, firstSynName, resultTable);
//    filterResultTableLinkageSet(secondSynName, secondSynValues, firstSynName, resultTable);
//    
//}
//
////first synonym is the synoym to combine, second is the linked synonym
//void ClauseHandler::filterCurrResult(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynCurrValues,
//    std::string secondSynName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynCurrValues, ResultTable& resultTable) {
//    std::unordered_map<std::string, SynonymLinkageMap> firstSynTableValues = resultTable.getSynonymEntry(firstSynName);
//    std::set<std::string> synValuesToRemove;
//    for (auto firstSynCurrValue : firstSynCurrValues) {
//        //can't find this synonym value in table, then delete it in current result
//        if (firstSynTableValues.count(firstSynCurrValue.first) == 0) {
//            //since only 2 args, first arg can only be linked to second arg
//            //linkedSynValues is the set arg1 currValue keep indicating all the links of arg1 currValue with arg2
//            std::set<std::string> linkedSynValues = firstSynCurrValue.second.getLinkedSynValueSet(secondSynName);
//            for (auto linkedSynValue : linkedSynValues) {
//                //for all the values, go to arg2 and delete the linkage
//                secondSynCurrValues.at(linkedSynValue).deleteLinkage(firstSynName, firstSynCurrValue.first);
//                //since arg2 can only be linked to arg1, if the value contains no linkage with arg1, we can delete this value safely.
//                if (secondSynCurrValues.at(linkedSynValue).isEmptyLinkageSet(firstSynName)) {
//                    secondSynCurrValues.erase(linkedSynValue);
//                }
//            }
//            synValuesToRemove.insert(firstSynCurrValue.first);
//        }
//    }
//    for (auto synValueToRemove : synValuesToRemove) {
//        firstSynCurrValues.erase(synValueToRemove);
//    }
//}
//
//void ClauseHandler::filterResultTable(std::string currSynName, std::unordered_map<std::string, SynonymLinkageMap>& currSynValues, ResultTable& resultTable) {
//    std::unordered_map<std::string, SynonymLinkageMap> tableSynValues = resultTable.getSynonymEntry(currSynName);
//    for (auto tableSynValue : tableSynValues) {
//        //the entry can't be found in the current syn values, then delete the entry in table
//        if (currSynValues.count(tableSynValue.first) == 0) {
//            deleteSynTableEntry(currSynName, tableSynValue.first, resultTable);
//        }
//    }
//}

//void ClauseHandler::filterCurrResultLinkageSet(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynValues,
//    std::string secondSynName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynValues, ResultTable& resultTable) {
//    std::set<std::string> synValuesToDelete;
//    std::unordered_map<std::string, SynonymLinkageMap> firstSynTableValues = resultTable.getSynonymEntry(firstSynName);
//    for (auto currSynValue = firstSynValues.begin(); currSynValue != firstSynValues.end(); currSynValue++) {
//        SynonymLinkageMap& tableSynValueLinkageMap = resultTable.getSynonymEntry(firstSynName).at(currSynValue->first);
//        SynonymLinkageMap& currSynValueLinkageMap = currSynValue->second;
//        bool isTableFirstSecondSynLinked = !tableSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
//        bool isCurrFirstSecondSynLinked = !currSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
//        // if both table and current result contains the linkage set, find the intersection of them
//        if (isTableFirstSecondSynLinked && isCurrFirstSecondSynLinked) {
//            std::set<std::string> intersectedValues = Utility::getSetIntersection(
//                currSynValue->second.getLinkageMap().at(secondSynName),
//                tableSynValueLinkageMap.getLinkageMap().at(secondSynName));
//            std::set<std::string> linkageToDelete;
//            for (auto linkedValue : currSynValueLinkageMap.getLinkedSynValueSet(secondSynName)) {
//                if (intersectedValues.count(linkedValue) == 0) {
//                    linkageToDelete.insert(linkedValue);
//                    //currSynValueLinkageMap.deleteLinkage(secondSynName, );
//                    //currSynValueLinkageMap.getLinkageMap().at(secondSynName).erase(linkedValue);
//                    secondSynValues.at(linkedValue).deleteLinkage(firstSynName, currSynValue->first);
//                    //secondSynValues.at(linkedValue).getLinkageMap().find(firstSynName)->second.erase(currSynValue.first);
//                    if (secondSynValues.at(linkedValue).isEmptyLinkageSet(firstSynName)) {
//                        secondSynValues.erase(linkedValue);
//                    }
//                }
//            }
//            for (auto linkedValue : linkageToDelete) {
//                currSynValueLinkageMap.deleteLinkage(secondSynName, linkedValue);
//            }
//            if (currSynValueLinkageMap.getLinkedSynValueSet(secondSynName).size() == 0) {
//                synValuesToDelete.insert(currSynValue->first);
//            }
//        }
//        else if (!isTableFirstSecondSynLinked && isCurrFirstSecondSynLinked) {
//            tableSynValueLinkageMap.insertNewEntry(secondSynName, currSynValueLinkageMap.getLinkedSynValueSet(secondSynName));
//        }
//    }
//    for (auto synValue : synValuesToDelete) {
//        firstSynValues.erase(synValue);
//    }
//}

//void ClauseHandler::filterResultTableLinkageSet(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynValues,
//    std::string secondSynName, ResultTable& resultTable) {
//    std::unordered_map<std::string, SynonymLinkageMap>& firstSynTableValues = resultTable.getSynonymEntry(firstSynName);
//    std::set<std::string> synValuesToDelete;
//    for (auto tableSynValue = firstSynTableValues.begin(); tableSynValue != firstSynTableValues.end(); tableSynValue++) {
//        SynonymLinkageMap& tableSynValueLinkageMap = tableSynValue->second;
//        SynonymLinkageMap& currSynValueLinkageMap = firstSynValues.at(tableSynValue->first);
//        bool isTableFirstSecondSynLinked = !tableSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
//        bool isCurrFirstSecondSynLinked = !currSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
//        if (isTableFirstSecondSynLinked && isCurrFirstSecondSynLinked) {
//            std::set<std::string> intersectedValues = Utility::getSetIntersection(
//                firstSynValues.at(tableSynValue->first).getLinkedSynValueSet(secondSynName)
//                /*firstSynValues.find(tableSynValue.first)->second.getLinkageMap().find(secondSynName)->second*/,
//                tableSynValueLinkageMap.getLinkedSynValueSet(secondSynName));
//            std::set<std::string> linkedSynValues = tableSynValueLinkageMap.getLinkedSynValueSet(secondSynName);
//            std::set<std::string> synsToDelete;
//            for (auto linkedTableValue : linkedSynValues) {
//                if (intersectedValues.count(linkedTableValue) == 0) {
//                    deleteLinkageInTable(firstSynName, tableSynValue->first, secondSynName, linkedTableValue,  resultTable);
//                    synsToDelete.insert(linkedTableValue);
//                }
//            }
//            for (auto synToDelete : synsToDelete) {
//                tableSynValueLinkageMap.deleteLinkage(secondSynName, synToDelete);
//            }
//            if (tableSynValueLinkageMap.getLinkedSynValueSet(secondSynName).size() == 0) {
//                synValuesToDelete.insert(tableSynValue->first);
//            }
//        }
//        else if (!isTableFirstSecondSynLinked && isCurrFirstSecondSynLinked) {
//            tableSynValueLinkageMap.insertNewEntry(secondSynName, currSynValueLinkageMap.getLinkedSynValueSet(secondSynName));
//        }
//    }
//    for (auto tableSynValue : synValuesToDelete) {
//        firstSynTableValues.erase(tableSynValue);
//    }
//}

//void ClauseHandler::filterOneSynWithLinkage(std::string currSynName, std::unordered_map<std::string, SynonymLinkageMap>& currSynValues, std::string linkedSynName, ResultTable& resultTable) {
//    std::unordered_map<std::string, SynonymLinkageMap> tableSynValues = resultTable.getSynonymEntry(currSynName);
//    std::set<std::string> synValuesToRemove;
//    for (auto currSynValue : currSynValues) {
//        //can't find entry in table
//        if (tableSynValues.count(currSynValue.first) == 0) {
//            //since only 2 argument, first arg can only be linked to second arg
//            std::set<std::string> linkedSynValues = currSynValue.second.getLinkedSynValueSet(linkedSynName);
//            for (auto linkedSynValue : linkedSynValues) {
//                SynonymLinkageMap& tableLinkedSynMap = resultTable.getSynonymEntry(linkedSynName).at(linkedSynValue);
//                tableLinkedSynMap.deleteLinkage(currSynName, currSynValue.first);
//                    //getLinkageMap().find(currSynName)->second.erase(currSynValue.first);
//                if (tableLinkedSynMap.isEmptyLinkageSet(currSynName)) {
//                    resultTable.getSynonymEntry(linkedSynName).erase(linkedSynValue);
//                }
//            }
//            synValuesToRemove.insert(currSynValue.first);
//        }
//    }
//    for (auto synValueToRemove : synValuesToRemove) {
//        currSynValues.erase(synValueToRemove);
//    }
//}

//void ClauseHandler::filterOneSynLinkageSet(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynValues, 
//    std::string secondSynName, ResultTable &resultTable) {
//    std::unordered_map<std::string, SynonymLinkageMap> tableFirstSynValues = resultTable.getSynonymEntry(firstSynName);
//
//    for (auto currSynValue = firstSynValues.begin(); currSynValue != firstSynValues.end(); currSynValue++) {
//        SynonymLinkageMap& tableSynValueLinkageMap = resultTable.getSynonymEntry(firstSynName).at(currSynValue->first);
//        SynonymLinkageMap& currSynValueLinkageMap = currSynValue->second;
//        bool isTableFirstSecondSynLinked = !tableSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
//        bool isCurrFirstSecondSynLinked = !currSynValueLinkageMap.isEmptyLinkageSet(secondSynName);
//        if (isTableFirstSecondSynLinked && isCurrFirstSecondSynLinked) {
//            std::set<std::string> intersectedValues = Utility::getSetIntersection(
//                currSynValueLinkageMap.getLinkedSynValueSet(secondSynName),
//                tableSynValueLinkageMap.getLinkedSynValueSet(secondSynName));
//            for (auto linkedSynValue : currSynValueLinkageMap.getLinkedSynValueSet(secondSynName)) {
//                if (intersectedValues.count(linkedSynValue) == 0) {
//                    currSynValueLinkageMap.deleteLinkage(secondSynName, linkedSynValue);
//                        //.getLinkageMap().find(secondSynName)->second.erase(linkedSynValue);
//                    //now we are merging arg2 into resultTable, since arg2 contains linkage with arg1 and arg1 is now merged into resultTable, 
//                    //after deleting the link in arg2, we need to go through the resultTable and delete the link there.
//                    resultTable.getSynonymEntry(secondSynName).at(linkedSynValue).deleteLinkage(firstSynName, currSynValue->first);
//                        //getLinkageMap().find(firstSynName)->second.erase(currSynValue.first);
//                    if (resultTable.getSynonymEntry(secondSynName).at(linkedSynValue).isEmptyLinkageSet(firstSynName)) {
//                        resultTable.getSynonymEntry(secondSynName).erase(linkedSynValue);
//                    }
//                }
//            }
//        }
//        else if (!isTableFirstSecondSynLinked && isCurrFirstSecondSynLinked) {
//            tableSynValueLinkageMap.insertNewEntry(secondSynName, currSynValueLinkageMap.getLinkedSynValueSet(secondSynName));
//
//        }
//    }
//}

//void ClauseHandler::combineOneSynResult(std::string currSynName, std::unordered_map<std::string, SynonymLinkageMap>& currSynValues, ResultTable& resultTable) {
//    if (resultTable.isSynonymPresent(currSynName)) {
//        std::unordered_map<std::string, SynonymLinkageMap> tableSynValues = resultTable.getSynonymEntry(currSynName);
//        for (auto tableSynValue : tableSynValues) {
//            if (currSynValues.count(tableSynValue.first) == 0) {
//                deleteSynTableEntry(currSynName, tableSynValue.first, resultTable);
//            }
//        }
//        //mergeResultToTable(synonymName, synonymInstanceCollection, resultTable);
//    }
//    else {
//        resultTable.insertSynonymEntry(currSynName, currSynValues);
//    }
//}

//void ClauseHandler::deleteSynTableEntry(std::string synName, std::string synValue, ResultTable& resultTable) {
//    std::unordered_map<std::string, std::set<std::string>> tableLinkageMap = resultTable.getSynonymEntry(synName).at(synValue).getLinkageMap();
//    
//    //example: "11":{"stmt2":[12,13,14],"stmt3":[10,11,12]} iterate through all linked instance and delete them, then delete the synonym instance entry
//    for (pair<std::string, std::set<std::string>> linkedValueCollection : tableLinkageMap) {
//        for (std::string linkedValue : linkedValueCollection.second) {
//            deleteLinkageInTable(synName, synValue, linkedValueCollection.first, linkedValue,  resultTable);
//        }
//    }
//    resultTable.deleteSynonymInstance(synName, synValue);
//}

//void ClauseHandler::deleteSynValueInResult(std::string currSynName, std::string currSynValue, std::set<std::string> linkageSet, 
//    std::string linkedSynName, std::unordered_map<std::string, SynonymLinkageMap>& LinkedSynValues) {
//
//}

//go to the linked synonym and delete the link with the current synonym
//void ClauseHandler::deleteLinkageInTable(std::string synName, std::string synValue, 
//    std::string linkedSynName, std::string linkedSynInstance, ResultTable& resultTable) {
//    resultTable.getSynonymEntry(linkedSynName).at(linkedSynInstance).deleteLinkage(synName, synValue);
//
//    //example: "stmt2":{"6":{"stmt1": [5], "stmt2": [7]}}}, now delete 5, "stmt1" entry becomes empty, then "6" can't be selected now
//    if (resultTable.getSynonymEntry(linkedSynName).find(linkedSynInstance)->second.isEmptyLinkageSet(synName)) {
//        deleteSynTableEntry(linkedSynName, linkedSynInstance, resultTable);
//    }
//}

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
    else {
        std::set<int> allStmtIntSet;

        if (DeType == "stmt") {
           allStmtIntSet = pkb.getAllStmtNums();
        } else if (DeType == "assign") {
            allStmtIntSet = pkb.getAllStmtNumsByType("=");
        } else {
            allStmtIntSet = pkb.getAllStmtNumsByType(DeType);
        }

        for (int stmtNum: allStmtIntSet) {
            ret.insert(to_string(stmtNum));
        }
    }
    return ret;
}

void ClauseHandler::resultTableCheckAndAdd(string synName, ResultTable& resultTable, string DeType) {
    if (!resultTable.isSynExist(synName)) {
        Result result;


        // constructs temp resultTable to be merged into resultTable
        std::set<string> synValuesStrSet = getResultFromPKB(pkb, DeType);
        std::vector<string> synValuesStrVector(synValuesStrSet.begin(), synValuesStrSet.end());
        std::vector<std::vector<std::string>> tempResult = { synValuesStrVector };
        std::vector<string> synList = { synName };
        ResultTable tempResultTable = ResultTable(tempResult, synList);
        resultTable.combineTable(tempResultTable);


        //std::unordered_map<std::string, SynonymLinkageMap> synValues;
        //for (std::string synValueStr : synValuesStrSet) {
        //    synValues.insert(std::make_pair<>(synValueStr, SynonymLinkageMap()));
        //}
        //result.setFirstArg(synName, synValues);
        //ClauseHandler::combineResult(resultTable, result);
    }
}

