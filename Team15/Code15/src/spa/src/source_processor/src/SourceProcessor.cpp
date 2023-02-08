#include "../include/SourceProcessor.h"
#include <iostream>

using namespace std;

SourceProcessor::SourceProcessor() {
    tokeniser = new Tokeniser();
}

int main() {
    SourceProcessor *sourceProcessor = new SourceProcessor();
    Tokeniser* tokeniser = sourceProcessor->tokeniser;
    tokeniser->tokenise();
    return 0;
}