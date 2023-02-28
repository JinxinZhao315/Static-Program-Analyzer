//
// Created by Jinxin Zhao on 3/2/23.
//

#include "QPS/include/model/ResultTable.h"
ResultTable::ResultTable() {}

ResultTable::ResultTable(std::vector<std::vector<std::string>> resultTable, std::vector<std::string> synList) {
    this->resultTable = resultTable;
    this->synList = synList;
}

void ResultTable::combineTable(ResultTable tempResult) {
    /*if(resultTable.find(synonymName) == resultTable.end()) {
        this->resultTable.insert(std::make_pair<>(synonymName, synonymInstanceCollection));
    };*/
    if (isTableEmpty()) {
        this->resultTable = tempResult.resultTable;
        this->synList = tempResult.synList;
    }
    else {
        
        //index of the old synonym if they match the synonym in the new result
        std::vector<int> commonSynIndex;
        std::vector<std::string> tempSynList = tempResult.getSynList();
        for (int i = 0; i < tempSynList.size(); i++) {
            auto it = find(synList.begin(), synList.end(), tempSynList[i]);
            if (it != synList.end()) {
                commonSynIndex[i] = it - synList.begin();
            }
            else {
                commonSynIndex[i] = -1;
            }
        }

        std::vector<std::string> newSynList = synList;
        for (int i = 0; i < tempSynList.size(); i++) {
            if (commonSynIndex[i] < 0) {
                newSynList.push_back(tempSynList[i]);
            }
        }

        ResultTable newResultTable({}, newSynList);

        for (std::vector<std::string> oldTuple : resultTable) {
            for (std::vector<std::string> currTuple : tempResult.getResultTable()) {
                if (isValidMatch(oldTuple, currTuple, commonSynIndex)) {
                    newResultTable.insertTuple(mergeTuple(oldTuple, currTuple, commonSynIndex));
                }
            }
        }
        this->resultTable = newResultTable.resultTable;
        this->synList = newResultTable.synList;
    }
}

std::vector<std::string> ResultTable::mergeTuple(std::vector<std::string> oldTuple, std::vector<std::string> currTuple, std::vector<int> commonSynIndex) {
    for (int i = 0; i < currTuple.size(); i++) {
        if (commonSynIndex[i] < 0) {
            oldTuple.push_back(currTuple[i]);
        }
    }
    return oldTuple;
}

bool ResultTable::isValidMatch(std::vector<std::string> oldTuple, std::vector<std::string> currTuple, std::vector<int> commonSynIndex) {
    for (int i = 0; i < currTuple.size(); i++) {
        if (commonSynIndex[i] >= 0 && currTuple[i] != oldTuple[commonSynIndex[i]]) {
            return false;
        }
    }
    return true;
}







bool ResultTable::isSynonymPresent(std::string key) {
    if (this->resultTable.find(key) == this->resultTable.end()) {
        return false;
    } else {
        return true;
    }
}
//
std::unordered_map<std::string, SynonymLinkageMap>& ResultTable::getSynonymEntry(std::string key) {
    return this->resultTable.find(key)->second;
}

std::set<std::string> ResultTable::getStringSetFromKey(std::string synonymName) {
    std::unordered_map<std::string, SynonymLinkageMap> synonymResult = this->resultTable.find(synonymName)->second;
    std::set<std::string> synonymStringSet;
    for (auto synonymInstance : synonymResult) {
        synonymStringSet.insert(synonymInstance.first);
    }
    return synonymStringSet;
}



//void ResultTable::insertKeyValuePair(std::string key, std::set<std::string> value) {
//    this->resultTable.insert({key, value});
//}

int ResultTable::getSizeOfResultTable() {
    return resultTable.size();
} 

bool ResultTable::isKeyPresent(std::string key) {
    if (this->resultTable.find(key) == this->resultTable.end()) {
        return false;
    }
    else {
        return true;
    }
}
void ResultTable::deleteSynonymInstance(std::string synonymName, std::string synonymInstance) {
    this->resultTable.at(synonymName).erase(synonymInstance);
}
//
//void ResultTable::deleteKeyValuePair(std::string key) {
//    this->resultTable.erase(key);

//}

//delete for early exit, no linkage being deleted
void ResultTable::deleteKeyValuePair(std::string key) {
    this->resultTable.erase(key);
}

void ResultTable::resetKeySetEmpty(std::string selectedVarName) {
    deleteKeyValuePair(selectedVarName);
    insertSynonymEntry(selectedVarName, {});
}

bool ResultTable::existSynonymWithNoValue() {
    for (auto synonym : resultTable) {
        if (synonym.second.empty()) {
            return true;
        }
    }
    return false;
}