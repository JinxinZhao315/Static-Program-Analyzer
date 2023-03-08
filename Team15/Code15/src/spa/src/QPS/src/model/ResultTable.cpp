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





void ResultTable::combineTable(ResultTable tempResultTable) {
    //the table has just been initialized
    if (isSynListEmpty()) {
        this->resultTable = tempResultTable.resultTable;
        this->synList = tempResultTable.synList;
        this->rowNum = tempResultTable.rowNum;
        this->colNum = tempResultTable.colNum;
    }
    //to combine the resultTable that clause handler evaluate to true
    else if (isTableEmpty() || tempResultTable.isSynListEmpty()) {
        return;
    }
    //tempResultTable is empty, should also set the current resultTable to empty
    else if (tempResultTable.isTableEmpty()) {
        clearResultTable();
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





std::vector<std::string> ResultTable::getSynList() {
    return this->synList;
}

std::vector<std::vector<std::string>> ResultTable::getResultTable() {
    return this->resultTable;
}

int ResultTable::getRowNum() {
    return this->rowNum;
}

int ResultTable::getColNum() {
    return this->colNum;
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

std::vector<std::string> ResultTable::getTuple(int index) {
    std::vector<std::string> resultTuple;
    for (int i = 0; i < rowNum; i++) {
        resultTuple.push_back(resultTable[i][index]);
    }
    return resultTuple;
}

std::set<std::string> ResultTable::getSelectedResult(std::vector<std::string> selectedSynNames) {
    if (selectedSynNames.size() > 1) {
        std::vector<int> synNameIndex;
        //get the index of each synName in synList
        for (int i = 0; i < selectedSynNames.size(); i++) {
            std::vector<std::string>::iterator it = std::find(synList.begin(), synList.end(), selectedSynNames[i]);
            synNameIndex.push_back(it - synList.begin());
        }

        std::set<std::string> multiSynResult;
        for (int i = 0; i < colNum; i++) {
            std::string tuple;
            for (int j = 0; j < selectedSynNames.size(); j++) {
                tuple += resultTable[synNameIndex[j]][i] + " ";
            }
            //pop the last white space
            tuple.pop_back();
            multiSynResult.insert(tuple);
        }
        return multiSynResult;
    }
    else if (selectedSynNames.size() == 1) {
        //BOOLEAN is a synonym
        if (selectedSynNames[0] != "BOOLEAN" || isSynExist("BOOLEAN")) {
            std::vector<std::string> selectedSynVec = getSynValues(selectedSynNames[0]);
            std::set<std::string> selectedSynResult(selectedSynVec.begin(), selectedSynVec.end());
            return selectedSynResult;
        }
        //BOOLEAN is BOOLEAN
        else {
            if (isTableEmpty()) {
                return { "FALSE" };
            }
            else {
                return { "TRUE" };
            }

        }
    }
}



//return true if there is no tuple in the table
bool ResultTable::isTableEmpty() {
    return this->colNum == 0;
}

bool ResultTable::isSynListEmpty() {
    return this->rowNum == 0;
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





void ResultTable::clearResultTable() {
    for (int i = 0; i < rowNum; i++) {
        this->resultTable[i] = {};
    }
    colNum = 0;
}

void ResultTable::deleteTuple(int index) {
    //traverse every row of the table
    if (index >= 0 && index < colNum) {
        for (int i = 0; i < resultTable.size(); i++) {
            this->resultTable[i].erase(resultTable[i].begin() + index);
        }
        colNum--;
    }
}

void ResultTable::insertTuple(std::vector<std::string> tuple) {
    if (tuple.size() == rowNum) {
        for (int i = 0; i < resultTable.size(); i++) {
            this->resultTable[i].push_back(tuple[i]);
        }
        colNum++;
    }
    else {
        //should throw exception ???
    }
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



