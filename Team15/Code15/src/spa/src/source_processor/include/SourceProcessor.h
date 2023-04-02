#include "tokeniser/Tokeniser.h"
#include "parser/Parser.h"
#include "extractor/Extractor.h"
#include "pkb/include/PKB.h"

class SourceProcessor {
private:
    Tokeniser *tokeniser;
    Parser *parser;
    Extractor *extractor;
    PKB *pkb;
public:
    SourceProcessor(PKB* pkb);
    void parseProgram(string fileName);
    void printParsedProgram();
    void extract(const vector<Line>& program);
    void storeDataInPKB();
};