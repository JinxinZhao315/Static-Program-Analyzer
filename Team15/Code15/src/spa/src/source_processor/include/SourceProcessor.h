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

    // TODO: get pkb to use these
    bool getAffectsRS(int lineNum1, int lineNum2);
    bool getAffectsStarRS(int lineNum1, int lineNum2);
    set<int> getAffectsRSWithWildcard(int lineNum, bool wildcardIsFirstArg);
    set<int> getAffectsStarRSWithWildcard(int lineNum, bool wildcardIsFirstArg);
};