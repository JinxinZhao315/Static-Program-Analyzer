#include "../include/SourceProcessor.h"
#include "../include/parser/Line.h"
#include <iostream>

using namespace std;

SourceProcessor::SourceProcessor() {
    tokeniser = new Tokeniser();
    parser = new Parser();
    extractor = new Extractor();
}

void SourceProcessor::parseProgram(string fileName) {
    parser->parseProgram(fileName);
    tokeniser->feedLines(fileName);
    vector<Line> extractedLines = tokeniser->getExtractedLines();
    extract(extractedLines);
}

void SourceProcessor::storeDataInPKB(PKB* pkb) {
    pkb->addAllProcs(extractor->getProcedures());
    pkb->addAllVars(extractor->getVariables());
    pkb->addAllConsts(extractor->getConstants());
    pkb->addAllStmtsByType(extractor->getStatements());
    pkb->addAllFollows(extractor->getFollowsRS());
    pkb->addAllFollowsStar(extractor->getFollowsStarRS());
    pkb->addAllParent(extractor->getParentRS());
    pkb->addAllParentStar(extractor->getParentStarRS());
    pkb->addAllModifiesStmt(extractor->getModifiesRS());
    pkb->addAllUsesStmt(extractor->getUsesRS());
//    pkb->addPatt(); //TODO: finish this after PKB api is implemented
//    extractor->getAssignsRS()
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
