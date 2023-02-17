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

void SourceProcessor::storeDataInPKB() {
    //TODO: all API calls to PKB
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
