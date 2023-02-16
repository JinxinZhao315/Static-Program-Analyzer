//
// Created by Jinxin Zhao on 3/2/23.
//

#include "QPS/include/model/ResultTable.h"
ResultTable::ResultTable() {}
ResultTable::ResultTable(std::unordered_map<std::string, std::unordered_map<std::string, SynonymLinkageMap>> resultTable) {
    this->resultTable = resultTable;
}

void ResultTable::insertSynonymEntry(std::string synonymName, std::unordered_map<std::string, SynonymLinkageMap> synonymInstanceCollection) {
    if(resultTable.find(synonymName) == resultTable.end()) {
        this->resultTable.insert(std::make_pair<>(synonymName, synonymInstanceCollection));
    };

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