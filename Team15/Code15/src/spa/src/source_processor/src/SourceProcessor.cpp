#include "source_processor//include/SourceProcessor.h"
#include "common/include/models/Line.h"
#include <iostream>

using namespace std;

SourceProcessor::SourceProcessor() {
    tokeniser = new Tokeniser();
    parser = new Parser();
    extractor = new Extractor();
}

void SourceProcessor::parseProgram(string fileName) {
    parser->parseProgram(fileName);
    tokeniser->feedLines(parser->getParsedProgram());
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    extract(extractedLines);
}

void SourceProcessor::storeDataInPKB(PKB* pkb) {
    pkb->addAllProcs(extractor->getProcedures());
    pkb->addAllVars(extractor->getVariables());
    pkb->addAllConsts(extractor->getConstants());
    // pkb->addAllStmts(extractor->getStatements());
    pkb->addAllFollows(extractor->getFollowsRS());
    pkb->addAllFollowsStar(extractor->getFollowsStarRS());
    pkb->addAllParent(extractor->getParentRS());
    pkb->addAllParentStar(extractor->getParentStarRS());
    pkb->addAllModifiesStmt(extractor->getModifiesRS());
    pkb->addAllUsesStmt(extractor->getUsesRS());
    pkb->addAllAssignPatterns(extractor->getAssignsRS());
    pkb->addAllIfPatterns(extractor->getIfRS());
    pkb->addAllWhilePatterns(extractor->getWhileRS());
    pkb->addAllUsesProc(extractor->getProcedureUsesRS());
    pkb->addAllModifiesProc(extractor->getProcedureModifiesRS());
    pkb->addAllCalls(extractor->getCallsRS());
    pkb->addAllCallsStar(extractor->getCallsStarRS());
    pkb->addAllWithRead(extractor->getReadLineNumToVarName());
    pkb->addAllWithPrint(extractor->getPrintLineNumToVarName());
    pkb->addAllWithCall(extractor->getCallLineNumToProcName());
    pkb->addAllNext(extractor->getNextRS());
    //TODO
    //Next*: pkb->addAllNextStar();
    //Affects: pkb->addAllAffects();
    //Affects*: pkb->addAllAffectsStar();
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
