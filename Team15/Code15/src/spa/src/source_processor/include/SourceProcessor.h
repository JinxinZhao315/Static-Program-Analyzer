#pragma once

#include "tokeniser/Tokeniser.h"
#include "parser/Parser.h"
#include "extractor/Extractor.h"
#include "pkb/include/PKB.h"

class PKB;
class Extractor;
class Tokeniser;
class Parser;

class SourceProcessor {
private:
    Tokeniser *tokeniser;
    Parser *parser;
    Extractor *extractor;
    PKB* pkb;
public:
    SourceProcessor();
    void parseProgram(string fileName);
    void printParsedProgram();
    void extract(const vector<Line>& program);
    void storeDataInPKB(PKB* pkb);

    // TODO: get pkb to use these
    bool getAffectsRS(int lineNum1, int lineNum2, const vector<Line>& program, const unordered_map<int,
            set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
            const unordered_map<int, set<int>>& cfg);
    bool getAffectsStarRS(int lineNum1, int lineNum2, const vector<Line>& program, const unordered_map<int,
            set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
            const unordered_map<int, set<int>>& cfg);
    set<int> getAffectsRSWithWildcard(int lineNum, bool wildcardIsFirstArg, const vector<Line>& program, const unordered_map<int,
            set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
            const unordered_map<int, set<int>>& cfg);
    set<int> getAffectsStarRSWithWildcard(int lineNum, bool wildcardIsFirstArg, const vector<Line>& program, const unordered_map<int,
            set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
            const unordered_map<int, set<int>>& cfg);
    unordered_map<int, set<int>> getAffectsRSWithMultipleWildcards(const vector<Line>& program, const unordered_map<int,
            set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
            const unordered_map<int, set<int>>& cfg);
    unordered_map<int, set<int>> getAffectsStarRSWithMultipleWildcards(const vector<Line>& program, const unordered_map<int,
            set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
            const unordered_map<int, set<int>>& cfg);
};