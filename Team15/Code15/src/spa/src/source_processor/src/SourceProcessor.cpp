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
    pkb->addAllVars(this->extractor->getVariables());
    pkb->addAllConsts(this->extractor->getConstants());
    pkb->addAllStmtsByType(this->extractor->getStatements());
    // TODO
    // add follows
    // add followsStar
    // add parent
    // add parent star
    // add modifies
    // add uses
    // add assigns
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

int main() {
    cout << "Creating source processor" << endl;
    string fileName = "../../../../../../Tests15/Sample_source.txt";
    SourceProcessor *sourceProcessor = new SourceProcessor();
    sourceProcessor->parseProgram(fileName);
    sourceProcessor->printParsedProgram(); //Optional
    return 0;
}
