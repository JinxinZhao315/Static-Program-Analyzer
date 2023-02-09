#include "../include/SourceProcessor.h"
#include <iostream>

using namespace std;

SourceProcessor::SourceProcessor() {
    tokeniser = new Tokeniser();
}

int main() {
    SourceProcessor *sourceProcessor = new SourceProcessor();
    Tokeniser* tokeniser = sourceProcessor->tokeniser;
    vector<string>* tokens = tokeniser->tokenise("procedureexample{if(a==b){returntrue;}}");
    for(string token : *tokens) {
        cout << token << endl;
    }
    return 0;
}
