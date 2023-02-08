#include "../include/SourceProcessor.h"
#include <iostream>

using namespace std;

SourceProcessor::SourceProcessor() {}

void SourceProcessor::print() {
    cout << "test" << endl;
}

int main() {
    SourceProcessor *sourceProcessor = new SourceProcessor();
    sourceProcessor->print();
    return 0;
}