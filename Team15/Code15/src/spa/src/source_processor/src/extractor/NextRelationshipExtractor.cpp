#include "source_processor/include/extractor/NextRelationshipExtractor.h"

//              procedure Second {
//        01        x = 0;
//        02        i = 5;
//        03        while (i!=0) {
//        04            x = x + 2*y;
//        05            call Third;
//        06            i = i - 1; }
//        07        if (x==1) then {
//        08            x = x+1; }
//                  else {
//        09            z = 1; }
//        10        z = z + x + i;
//        11        y = z + 2;
//        12        x = x * y + z; }

bool hasLineNumber(string keyword) {
    return !(keyword == "procedure" || keyword == "else" || keyword == "}");
}

unordered_map<int, int> extractNextRS(const vector<Line>& program) {
    unordered_map<int, int> nextRS;
    unordered_map<int, int> currentProcNextRS;
    int prevLineNumber = 0;
    for (int i = 0; i < program.size(); i++) {
        Line line = program[i];
        string type = line.getType();
        int currLineNumber = line.getLineNumber();
        if(type == "procedure") {
            nextRS.insert(currentProcNextRS.begin(), currentProcNextRS.end());
            currentProcNextRS.clear();
        } else if (type == "if") {
            // get lineNumber of first line after else
            int nesting = 0;
            for(int j = i + 1; j < program.size(); j++) {
                Line newLine = program[j];
                int newLineNumber = newLine.getLineNumber();
                string newLineType = newLine.getType();
                if(newLineType == "{") {
                    nesting++;
                } else if(newLineType == "}") {
                    nesting--;
                } else if(newLineType == "else" && nesting == 0) {
                    // for every next where the second val is the if ln,
                    // add a copy with the ln of the first line after else
                    for(auto entry : currentProcNextRS) {
                        if(entry.second == currLineNumber) {
                            currentProcNextRS.insert({entry.second, newLineNumber + 1});
                        }
                    }
                }
            }
        } else if (type == "while") {
            // get the line number of the first line after the while
            int nesting = 0;
            for(int j = i + 1; j < program.size(); j++) {
                Line newLine = program[j];
                int newLineNumber = newLine.getLineNumber();
                string newLineType = newLine.getType();
                if (newLineType == "{") {
                    nesting++;
                } else if (newLineType == "}") {
                    nesting--;
                    if(nesting == 0) {
                        for(auto entry : currentProcNextRS) {
                            if(entry.second == currLineNumber) {
                                currentProcNextRS.insert({entry.second, newLineNumber + 1});
                            }
                        }
                    }
                }
            }
        } else if(currLineNumber >= 1) {
            currentProcNextRS.insert({prevLineNumber, currLineNumber});
        }
        if(hasLineNumber(type)) {
            prevLineNumber++;
        }
    }
    return nextRS;
}