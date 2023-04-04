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
        this->synValMap.insert(std::make_pair<>(synList[i], set<std::string>({})));
    }
}

ResultTable::ResultTable(std::vector<std::string> synResult, std::string synName) {
    this->resultTable = { synResult };
    this->synList = { synName };
    std::set<std::string> synVal(synResult.begin(), synResult.end());
    this->synValMap.insert(std::make_pair<>(synName, synVal));
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
    for (int i = 0; i < resultTable.size(); i++) {
        std::vector<std::string> synVec = resultTable[i];
        std::string synName = synList[i];
        std::set<std::string> synVal(synVec.begin(), synVec.end());
        this->synValMap.insert(std::make_pair<>(synName, synVal));
    }
}

void ResultTable::resultTableCheckAndAdd(string synName, PKB pkb, string DeType) {
    if (!isSynExist(synName)) {

        std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, DeType);
        std::vector<string> synValuesStrVector(synValuesStrSet.begin(), synValuesStrSet.end());
        std::vector<std::vector<std::string>> tempResult = { synValuesStrVector };
        std::vector<string> synList = { synName };
        ResultTable tempResultTable = ResultTable(tempResult, synList);
        combineTable(tempResultTable);

    }
}

void ResultTable::combineTable(ResultTable tempResultTable) {
    //the table has just been initialized
    if (isSynListEmpty()) {
        this->resultTable = tempResultTable.resultTable;
        this->synList = tempResultTable.synList;
        this->rowNum = tempResultTable.rowNum;
        this->colNum = tempResultTable.colNum;
        this->synValMap = tempResultTable.synValMap;
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
                    newResultTable.insertTuple(Utility::mergeTuple(oldTuple, currTuple, commonSynIndex));
                }
            }
        }
        this->resultTable = newResultTable.resultTable;
        this->synList = newResultTable.synList;
        this->rowNum = newResultTable.rowNum;
        this->colNum = newResultTable.colNum;
        this->synValMap = newResultTable.synValMap;
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

std::set<std::string> ResultTable::getSynValues(std::string synName) {
    return this->synValMap.at(synName);
}

std::vector<std::string> ResultTable::getTuple(int index) {
    std::vector<std::string> resultTuple;
    for (int i = 0; i < rowNum; i++) {
        resultTuple.push_back(resultTable[i][index]);
    }
    return resultTuple;
}

std::string ResultTable::getAttrRefValue(int synIndex, int colIndex, AttrRef attrRef, PKB &pkb) {
    //attrbute is in the table
    if (attrRef.getAttrName() == "stmt#" || attrRef.getAttrName() == "value" ||
        attrRef.getSynType() == "procedure" || attrRef.getSynType() == "variable") {
        return resultTable[synIndex][colIndex];
    }
    else if (attrRef.getSynType() == "call") {
        int callLineNum = stoi(resultTable[synIndex][colIndex]);
        std::string calledProcName = pkb.getWithCallProcName(callLineNum, "-1");
        if (calledProcName == "-1") {
            //should throw error
        }
        return calledProcName;
    }
    else if (attrRef.getSynType() == "read") {
        int readLineNum = stoi(resultTable[synIndex][colIndex]);
        std::string readVarName = pkb.getWithReadVarName(readLineNum, "-1");
        if (readVarName == "-1") {
            //should throw error
        }
        return readVarName;
    }
    else if (attrRef.getSynType() == "print") {
        int printLineNum = stoi(resultTable[synIndex][colIndex]);
        std::string printVarName = pkb.getWithPrintVarName(printLineNum, "-1");
        if (printVarName == "-1") {
            //should throw error
        }
        return printVarName;
    }
    else {
        return "-1";
    }
}

std::set<std::string> ResultTable::getSelectedResult(std::vector<Elem> selectedElem, PKB &pkb, bool isEarlyExit) {
    if (selectedElem.size() > 1) {
        if (isEarlyExit) {
            return {};
        }
        std::vector<int> synNameIndex;
        //get the index of each synName in synList
        for (auto & elem : selectedElem) {
            auto it = std::find(synList.begin(), synList.end(), elem.getSynName());
            synNameIndex.push_back(it - synList.begin());
        }

        std::set<std::string> multiSynResult;
        for (int i = 0; i < colNum; i++) {
            std::string tuple;
            for (int j = 0; j < selectedElem.size(); j++) {
                if (selectedElem[j].isElemSynonym()) {
                    tuple += resultTable[synNameIndex[j]][i] + " ";
                }
                else {
                    tuple += getAttrRefValue(synNameIndex[j], i, selectedElem[j].getAttrRef(), pkb) + " ";
                }
            }
            //pop the last white space
            tuple.pop_back();
            multiSynResult.insert(tuple);
        }
        return multiSynResult;
    }
    else if (selectedElem.size() == 1) {
        //not BOOLEAN or BOOLEAN is a synonym
        if (selectedElem[0].getSynName() != "BOOLEAN" || isSynExist("BOOLEAN")) {
            if (isEarlyExit) {
                return {};
            }
            //std::set<std::string> selectedSynResult;
            //std::set<std::string> synValues = getSynValues(selectedElem[0].getSynName());
            //for (std::string syn : synValues) {
            //    if (selectedElem[0].isElemSynonym()) {
            //        selectedSynResult.insert(syn);
            //    }
            //    else {
            //        selectedSynResult.insert(getAttrRefValue(synIndex, i, selectedElem[0].getAttrRef(), pkb));
            //    }
            //}
            std::vector<std::string>::iterator it = std::find(synList.begin(), synList.end(), selectedElem[0].getSynName());

            int synIndex = it - synList.begin();
            std::set<std::string> selectedSynResult;
            for (int i = 0; i < colNum; i++) {
                if (selectedElem[0].isElemSynonym()) {
                    selectedSynResult.insert(resultTable[synIndex][i]);
                }
                else {
                    selectedSynResult.insert(getAttrRefValue(synIndex, i, selectedElem[0].getAttrRef(), pkb));
                }
            }
            return selectedSynResult;
        }
        //BOOLEAN is BOOLEAN
        else {
            //no tuple satisfy the condition, there are some synonyms, or no synonym is declared in the later clause but clause evaluate to false
            if ((isTableEmpty() && !isSynListEmpty()) || isEarlyExit) {
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

void ResultTable::insertTuple(std::vector<std::string> tuple) {
    if (tuple.size() == rowNum) {
        for (int i = 0; i < resultTable.size(); i++) {
            this->resultTable[i].push_back(tuple[i]);
            std::string synName = this->synList[i];
            this->synValMap.at(synName).insert(tuple[i]);
        }
        colNum++;
    }
    else {
        throw runtime_error("Result table tuple size != row number");
    }
}

void ResultTable::deleteSynonym(std::string synonym) {
    auto synNamePos = std::find(synList.begin(), synList.end(), synonym);
    int synIndex = std::distance(synList.begin(), synNamePos);
    if (synNamePos != synList.end()) {
        synList.erase(synNamePos);
        rowNum--;
        resultTable.erase(resultTable.begin() + synIndex);
        removeDuplicates();
    }
}

void ResultTable::removeDuplicates() {
    std::set<std::vector<std::string>> distinctTupleSet;
    for (int i = 0; i < colNum; i++) {
        std::vector<std::string> tuple = getTuple(i);
        if (tuple.size() > 0) {
            distinctTupleSet.insert(getTuple(i));
        }
    }
    resultTable = {};
    for (int i = 0; i < rowNum;i++) {
        this->resultTable.push_back({});
    }
    for (std::vector<std::string> distinctTuple : distinctTupleSet) {
        insertTuple(distinctTuple);
    }
    colNum = distinctTupleSet.size();
}

bool ResultTable::containsSyn(std::string syn) {
    return find(synList.begin(), synList.end(), syn) != synList.end();
}