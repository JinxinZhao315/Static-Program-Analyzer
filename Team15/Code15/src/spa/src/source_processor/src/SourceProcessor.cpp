#include "../include/SourceProcessor.h"
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
}

void SourceProcessor::storeDataInPKB() {
    //TODO: all API calls to PKB
}

void SourceProcessor::printParsedProgram() {
    cout << "Printing parsed program..." << endl;
    parser->printParsedProgram();
    cout << endl << "Printing extracted tokens..." << endl;
    tokeniser->printTokens();
}

void SourceProcessor::extract() {
    extractor-> extract();
}

int main() {
    cout << "Creating source processor" << endl;
    string fileName = "../../../../../../Tests15/Sample_source.txt";

    SourceProcessor *sourceProcessor = new SourceProcessor();
    sourceProcessor->parseProgram(fileName);
    sourceProcessor->printParsedProgram(); //Optional
    return 0;
}
