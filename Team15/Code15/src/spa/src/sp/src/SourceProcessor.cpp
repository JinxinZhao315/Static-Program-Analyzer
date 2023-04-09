#include "sp/include/SourceProcessor.h"
#include "common/include/models/Line.h"
#include <iostream>

using namespace std;

SourceProcessor::SourceProcessor() {
    tokeniser = new Tokeniser();
    parser = new Parser();
    extractor = new Extractor();
}

void SourceProcessor::parseProgram(string fileName, PKB* pkb) {
    parser->parseProgram(fileName);
    tokeniser->feedLines(parser->getParsedProgram());
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    pkb->addAllLines(extractedLines);
    extract(extractedLines);
    clearCache();
}

void SourceProcessor::storeDataInPKB(PKB* pkb) {
    pkb->addAllProcs(extractor->getProcedures());
    pkb->addAllVars(extractor->getVariables());
    pkb->addAllConsts(extractor->getConstants());
    pkb->addAllStmts(extractor->getStatements());
    pkb->addAllFollows(extractor->getFollowsRS());
    pkb->addAllFollowsStar(extractor->getFollowsStarRS());
    pkb->addAllParent(extractor->getParentRS());
    pkb->addAllParentStar(extractor->getParentStarRS());
    pkb->addAllUsesStmt(extractor->getUsesRS());
    pkb->addAllUsesProc(extractor->getProcedureUsesRS());
    pkb->addAllModifiesStmt(extractor->getModifiesRS());
    pkb->addAllModifiesProc(extractor->getProcedureModifiesRS());
    pkb->addAllCalls(extractor->getCallsRS());
    pkb->addAllCallsStar(extractor->getCallsStarRS());
    pkb->addAllNext(extractor->getNextRS());
    pkb->addAllWithRead(extractor->getReadLineNumToVarName());
    pkb->addAllWithPrint(extractor->getPrintLineNumToVarName());
    pkb->addAllWithCall(extractor->getCallLineNumToProcName());
    pkb->addAllAssignPatterns(extractor->getAssignsRS());
    pkb->addAllWhilePatterns(extractor->getWhileRS());
    pkb->addAllIfPatterns(extractor->getIfRS());
}

void SourceProcessor::printParsedProgram() {
    cout << "Printing parsed program..." << endl;
    parser->printParsedProgram();
    cout << endl << "Printing extracted tokens..." << endl;
    tokeniser->printLines();
    extractor->printEntities();
}

void SourceProcessor::extract(const vector<Line>& program) {
    extractor->extract(program);
}

bool SourceProcessor::getAffectsRS(int lineNum1, int lineNum2, const vector<Line>& program, const unordered_map<int,
        set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
                                   const unordered_map<int, set<int>>& cfg) {
    return extractor->getAffectsRS(lineNum1, lineNum2, program, modifies, uses, variablesForAffects, cfg);
}

bool SourceProcessor::getAffectsStarRS(int lineNum1, int lineNum2, const vector<Line>& program, const unordered_map<int,
        set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
                                       const unordered_map<int, set<int>>& cfg) {
    return extractor->getAffectsStarRS(lineNum1, lineNum2, program, modifies, uses, variablesForAffects, cfg);
}

set<int> SourceProcessor::getAffectsRSWithWildcard(int lineNum, bool wildcardIsFirstArg, const vector<Line>& program, const unordered_map<int,
        set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
                                                   const unordered_map<int, set<int>>& cfg) {
    return extractor->getAffectsRSWithWildcard(lineNum, wildcardIsFirstArg, program, modifies, uses, variablesForAffects, cfg);
}

set<int> SourceProcessor::getAffectsStarRSWithWildcard(int lineNum, bool wildcardIsFirstArg, const vector<Line>& program, const unordered_map<int,
        set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
                                                       const unordered_map<int, set<int>>& cfg) {
    return extractor->getAffectsStarRSWithWildcard(lineNum, wildcardIsFirstArg, program, modifies, uses, variablesForAffects, cfg);
}

unordered_map<int, set<int>> SourceProcessor::getAffectsRSWithMultipleWildcards(const vector<Line>& program, const unordered_map<int,
        set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
                                                                                const unordered_map<int, set<int>>& cfg) {
    return extractor->getAffectsRSWithMultipleWildcards(program, modifies, uses, variablesForAffects, cfg);
}

unordered_map<int, set<int>> SourceProcessor::getAffectsStarRSWithMultipleWildcards(const vector<Line>& program, const unordered_map<int,
        set<string>>& modifies, const unordered_map<int, set<string>>& uses, const set<string>& variablesForAffects,
                                                                                    const unordered_map<int, set<int>>& cfg) {
    return extractor->getAffectsStarRSWithMultipleWildcards(program, modifies, uses, variablesForAffects, cfg);
}

unordered_map<int, set<int>> SourceProcessor::getNextStarRS(const unordered_map<int, set<int>>& nextRS) {
    return extractNextStarRS(nextRS);
}
