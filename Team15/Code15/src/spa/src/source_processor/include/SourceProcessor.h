#include "tokeniser/Tokeniser.h"
#include "parser/Parser.h"

class SourceProcessor {
private:
    Tokeniser *tokeniser;
    Parser *parser;
public:
    SourceProcessor();
    void parseProgram(string fileName);
    void printParsedProgram();
    void storeDataInPKB();
};