//
// Created by Jinxin Zhao on 3/2/23.
//

#include "QPS/include/model/ResultTable.h"
ResultTable::ResultTable() {
    this->resultTable = {};
    this->synList = {};
    this->rowNum = 0;
    this->colNum = 0;
}

ResultTable::ResultTable(std::vector<std::string> synList) {
    this->synList = synList;
    this->rowNum = synList.size();
    this->colNum = 0;
    for (int i = 0; i < synList.size();i++) {
        this->resultTable.push_back({});
    }
}

ResultTable::ResultTable(std::vector<std::string> synResult, std::string synName) {
    this->resultTable = { synResult };
    this->synList = { synName };
    this->colNum = synResult.size();
    this->rowNum = 1;
}

ResultTable::ResultTable(std::vector<std::vector<std::string>> resultTable, std::vector<std::string> synList) {
    this->resultTable = resultTable;
    this->synList = synList;
    this->rowNum = synList.size();
    this->colNum = 0;
    if (resultTable.size() > 0) {
        this->colNum = resultTable[0].size();
    }
}


std::vector<std::string> ResultTable::getSynList() {
    return this->synList;
}

void ResultTable::combineTable(ResultTable tempResultTable) {
    /*if(resultTable.find(synonymName) == resultTable.end()) {
        this->resultTable.insert(std::make_pair<>(synonymName, synonymInstanceCollection));
    };*/
    if (isTableEmpty()) {
        this->resultTable = tempResultTable.resultTable;
        this->synList = tempResultTable.synList;
        this->rowNum = tempResultTable.rowNum;
        this->colNum = tempResultTable.colNum;
    }
    //to combine the resultTable that clause handler evaluate to true
    else if (tempResultTable.isTableEmpty()) {
        return;
    }
    else {
        
        //index of the old synonym if they match the synonym in the new result
        std::vector<int> commonSynIndex;
        std::vector<std::string> tempSynList = tempResultTable.getSynList();
        for (int i = 0; i < tempSynList.size(); i++) {
            std::vector<std::string>::iterator it = std::find(synList.begin(), synList.end(), tempSynList[i]);
            if (it != synList.end()) {
                commonSynIndex.push_back(it - synList.begin());
            }
            else {
                commonSynIndex.push_back(-1);
            }
        }

        // update the merged new synonym list
        std::vector<std::string> newSynList = synList;
        for (int i = 0; i < tempSynList.size(); i++) {
            //this synonym is a new synonym
            if (commonSynIndex[i] < 0) {
                newSynList.push_back(tempSynList[i]);
            }
        }

        ResultTable newResultTable(newSynList);

        for (int i = 0; i < colNum; i++) {
            std::vector<std::string> oldTuple = getTuple(i);
            for (int j = 0; j < tempResultTable.colNum; j++) {
                std::vector<std::string> currTuple = tempResultTable.getTuple(j);
                if (isTupleMatch(oldTuple, currTuple, commonSynIndex)) {
                    newResultTable.insertTuple(mergeTuple(oldTuple, currTuple, commonSynIndex));
                }
            }
        }
        this->resultTable = newResultTable.resultTable;
        this->synList = newResultTable.synList;
        this->rowNum = newResultTable.rowNum;
        this->colNum = newResultTable.colNum;
    }
}

bool ResultTable::isTableEmpty() {
    return this->resultTable.size() == 0 || this->synList.size() == 0;
}

std::vector<std::vector<std::string>> ResultTable::getResultTable() {
    return this->resultTable;
}

std::vector<std::string> ResultTable::getSynValues(std::string synName) {
    std::vector<std::string>::iterator itr = std::find(this->synList.begin(), this->synList.end(), synName);
    int index = -1;
    std::vector<std::string> synValues;
    if (itr != this->synList.cend()) {
        index = std::distance(this->synList.begin(), itr);
    }
    else {
        return {};
    }
    return this->resultTable[index];
}

std::set<std::string> ResultTable::getStringSetFromKey(std::string synName) {
    std::vector<std::string> synValuesVec = getSynValues(synName);
    std::set<std::string> synValuesSet(synValuesVec.begin(), synValuesVec.end());
    return synValuesSet;
}

void ResultTable::clearResultTable() {
    for (int i = 0; i < rowNum; i++) {
        this->resultTable[i] = {};
    }
    rowNum = 0;
}

bool ResultTable::isSynExist(std::string synName) {
    if (std::count(this->synList.begin(), this->synList.end(), synName)) {
        return true;
    }
    else {
        return false;
    }
}

bool ResultTable::isTupleMatch(std::vector<std::string> oldTuple, std::vector<std::string> currTuple, std::vector<int> commonSynIndex) {
    for (int i = 0; i < currTuple.size(); i++) {
        if (commonSynIndex[i] >= 0 && currTuple[i] != oldTuple[commonSynIndex[i]]) {
            return false;
        }
    }
    return true;
}

void ResultTable::deleteTuple(int index) {
    //traverse every row of the table
    for (int i = 0; i < resultTable.size(); i++) {
        this->resultTable[i].erase(resultTable[i].begin() + index);
    }
    colNum--;
}

void ResultTable::insertTuple(std::vector<std::string> tuple) {
    for (int i = 0; i < resultTable.size(); i++) {
        this->resultTable[i].push_back(tuple[i]);
    }
    colNum++;
}

std::vector<std::string> ResultTable::mergeTuple(std::vector<std::string> oldTuple, std::vector<std::string> currTuple, std::vector<int> commonSynIndex) {
    std::vector<std::string> resultTuple = oldTuple;
    for (int i = 0; i < currTuple.size(); i++) {
        if (commonSynIndex[i] < 0) {
            resultTuple.push_back(currTuple[i]);
        }
    }
    return resultTuple;
}

std::vector<std::string> ResultTable::getTuple(int index) {
    std::vector<std::string> resultTuple;
    for (int i = 0; i < rowNum; i++) {
        resultTuple.push_back(resultTable[i][index]);
    }
    return resultTuple;
}






//bool ResultTable::isSynonymPresent(std::string key) {
//    if (this->resultTable.find(key) == this->resultTable.end()) {
//        return false;
//    } else {
//        return true;
//    }
//}
////
//std::unordered_map<std::string, SynonymLinkageMap>& ResultTable::getSynonymEntry(std::string key) {
//    return this->resultTable.find(key)->second;
//}
//
//std::set<std::string> ResultTable::getStringSetFromKey(std::string synonymName) {
//    std::unordered_map<std::string, SynonymLinkageMap> synonymResult = this->resultTable.find(synonymName)->second;
//    std::set<std::string> synonymStringSet;
//    for (auto synonymInstance : synonymResult) {
//        synonymStringSet.insert(synonymInstance.first);
//    }
//    return synonymStringSet;
//}
//
//
//
////void ResultTable::insertKeyValuePair(std::string key, std::set<std::string> value) {
////    this->resultTable.insert({key, value});
////}
//
//int ResultTable::getSizeOfResultTable() {
//    return resultTable.size();
//} 
//
//bool ResultTable::isKeyPresent(std::string key) {
//    if (this->resultTable.find(key) == this->resultTable.end()) {
//        return false;
//    }
//    else {
//        return true;
//    }
//}
//void ResultTable::deleteSynonymInstance(std::string synonymName, std::string synonymInstance) {
//    this->resultTable.at(synonymName).erase(synonymInstance);
//}
////
////void ResultTable::deleteKeyValuePair(std::string key) {
////    this->resultTable.erase(key);
//
////}
//
////delete for early exit, no linkage being deleted
//void ResultTable::deleteKeyValuePair(std::string key) {
//    this->resultTable.erase(key);
//}
//
//void ResultTable::resetKeySetEmpty(std::string selectedVarName) {
//    deleteKeyValuePair(selectedVarName);
//    insertSynonymEntry(selectedVarName, {});
//}
//
//bool ResultTable::existSynonymWithNoValue() {
//    for (auto synonym : resultTable) {
//        if (synonym.second.empty()) {
//            return true;
//        }
//    }
//    return false;
//}