#include "../include/SourceProcessor.h"
#include <iostream>

using namespace std;

SourceProcessor::SourceProcessor() {
    tokeniser = new Tokeniser();
    parser = new Parser();
}

void SourceProcessor::parseProgram(string fileName) {
    parser->parseProgram(fileName);
    // TODO: Adi - tokeniser should call tokenise function
    tokeniser->tokenise();
}

void SourceProcessor::storeDataInPKB() {
    //TODO: all API calls to PKB
}

void SourceProcessor::printParsedProgram() {
    parser->printParsedProgram();
}

int main() {
    cout << "Creating source processor" << endl;
    string fileName = "Team15/Tests15/Sample_source.txt";

    SourceProcessor *sourceProcessor = new SourceProcessor();

    sourceProcessor->parseProgram(fileName);
    sourceProcessor->printParsedProgram(); //Optional
    return 0;
}