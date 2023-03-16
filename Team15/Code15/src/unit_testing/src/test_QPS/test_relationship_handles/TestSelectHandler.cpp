#include "pkb/include/PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/evaluator/FollowsHandler.h"
#include "QPS/include/evaluator/SelectHandler.h"
#include "QPS/include/model/Elem.h"
#include "TestUtility.h"

#include "catch.hpp"

using namespace std;

void testSelectSynPkb(PKB& pkb) {
    pkb.addAllVars(set<string>({ "x", "n", "m" }));
    pkb.addAllConsts(set<string>({ "1", "5" }));

    unordered_map<string, set<int>> stmts;
    stmts.insert(make_pair("=", set<int>({ 2, 3})));
    stmts.insert(make_pair("if", set<int>({ 1 })));
    pkb.addAllStmts(stmts);

    unordered_map<string, set<Line>> assignPatterns;
    Line line2 = Line(2, vector<string>({ "n", "1", "+" }), "=");
    Line line3 = Line(3, vector<string>({ "m", "1", "-" }), "=");

    assignPatterns.insert(make_pair("n", set<Line>({ line2 })));
    assignPatterns.insert(make_pair("m", set<Line>({ line3 })));
    pkb.addAllAssignPatterns(assignPatterns);

    unordered_map<string, set<Line>> ifPatterns;
    Line line1 = Line(1, vector<string>({ "x", "5", ">" }), "if");
    ifPatterns.insert(make_pair("x", set<Line>({ line1 })));
    pkb.addAllIfPatterns(ifPatterns);

    // Line 1: if (x > 5) {
    // Line 2: n = n + 1 } else {
    // Line 3: m = m - 1}
}

string testSelect(string queryStr) {
    PKB pkb;

    unordered_map<string, set<int>> stmts;
    stmts.insert(make_pair("=", set<int>({ 1 })));
    stmts.insert(make_pair("while", set<int>({ 2 })));
    stmts.insert(make_pair("if", set<int>({ 3 })));
    stmts.insert(make_pair("print", set<int>({ 4 })));
    stmts.insert(make_pair("call", set<int>({ 5 })));
    stmts.insert(make_pair("read", set<int>({ 6 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars({ "x" });
    pkb.addAllConsts({ "1", "2" });
    pkb.addAllProcs({ "main", "foo" });
    string retStr = TestUtility::testDriver(queryStr, pkb);
    return retStr;

    /*
    procedure main{
        x = x + 1;--------------------1
        while (x > 1){----------------2
            if (x < 2) {--------------3
                print x;--------------4
            } else {
                call foo;-------------5
            }
        }
    }
    procedure foo{
        read x;-----------------------6
    }
    procedure: main, foo
    variable: x
    constant: 1, 2
    assign: 1
    while: 2
    if: 3
    print: 4
    call: 5
    read: 6
    */
}

TEST_CASE("Select Handler test 1") {
    SelectClause selectClause({ Elem("r") });
    std::multimap<std::string, std::string> varTable;
    ResultTable resultTable = ResultTable();

    varTable.insert(pair<std::string, std::string>("a1", "="));
    varTable.insert(pair<std::string, std::string>("a2", "="));
    varTable.insert(pair<std::string, std::string>("r", "read"));
    varTable.insert(pair<std::string, std::string>("i", "if"));
    varTable.insert(pair<std::string, std::string>("w", "while"));
    varTable.insert(pair<std::string, std::string>("c", "constant"));
    varTable.insert(pair<std::string, std::string>("ca", "call"));
    varTable.insert(pair<std::string, std::string>("p", "procedure"));


    PKB pkb;
    pkb.addAllProcs(set<string>({ "p" }));

    unordered_map<string, set<int>> stmts;
    stmts.insert(make_pair("=", set<int>({ 1, 2 })));
    stmts.insert(make_pair("read", set<int>({ 3, 7, 8 })));
    stmts.insert(make_pair("if", set<int>({ 4 })));
    stmts.insert(make_pair("while", set<int>({ 5 })));
    stmts.insert(make_pair("call", set<int>({ 6 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars(set<string>({ "x", "y", "z" }));
    pkb.addAllConsts(set<string>({ "10", "11", "12", "13"}));


    SelectHandler selectHandler = SelectHandler(pkb);
    std::vector<Elem> selectedVarName = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name

    set<std::string> retSet = resultTable.getSelectedResult(selectedVarName, pkb);
    REQUIRE(selectedVarName[0].getSynName() == "r");
    REQUIRE(retSet.size() == 3);
    REQUIRE(retSet.count("3") == 1);
    REQUIRE(retSet.count("7") == 1);
    REQUIRE(retSet.count("8") == 1);
}

TEST_CASE("Select Handler test 2") {

        PQLPreprocessor preprocessor;
        string queryStr = "constant c; Select c";
        Query query = Query();
        query = preprocessor.preprocess(queryStr);
        SelectClause selectClause = query.getSelectClause();

        std::multimap<std::string, std::string> varTable = query.getSynonymTable();
        ResultTable resultTable = ResultTable();

        PKB pkb;


        pkb.addAllConsts(set<string>({ "10", "11", "12", "13" }));

        SelectHandler selectHandler = SelectHandler(pkb);
        std::vector<Elem> selectedVarName = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name

        set<std::string> retSet = resultTable.getSelectedResult(selectedVarName, pkb);
        REQUIRE(selectedVarName[0].getSynName() == "c");
        REQUIRE(retSet.size() == 4);
        REQUIRE(retSet.count("10") == 1);
        REQUIRE(retSet.count("11") == 1);
        REQUIRE(retSet.count("12") == 1);
        REQUIRE(retSet.count("13") == 1);

}

TEST_CASE("Select Handler test 3: multiple synonyms") {

    PQLPreprocessor preprocessor;
    string queryStr = "variable a, b; constant c; Select <a,b,c> ";// variable: m, n, x; constant: 1, 5
    Query query = preprocessor.preprocess(queryStr);
    SelectClause selectClause = query.getSelectClause();

    std::multimap<std::string, std::string> varTable = query.getSynonymTable();
    ResultTable resultTable = ResultTable();

    PKB pkb;
    testSelectSynPkb(pkb);

    SelectHandler selectHandler = SelectHandler(pkb);
    std::vector<Elem> selectedSynName = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name
    std::vector<std::string> expectedSelectedSynName = { "a", "b", "c" };
    std::vector<std::vector<std::string>> expectedResultTable = {
        { "m", "m", "m", "m", "m", "m", "n", "n", "n", "n", "n", "n", "x", "x", "x", "x", "x", "x"},
        { "m", "m", "n", "n", "x", "x", "m", "m", "n", "n", "x", "x", "m", "m", "n", "n", "x", "x"},
        { "1", "5", "1", "5", "1", "5", "1", "5", "1", "5", "1", "5", "1", "5", "1", "5", "1", "5"}
    };

    


    REQUIRE(resultTable.getColNum() == 18);
    REQUIRE(resultTable.getRowNum() == 3);
    for (int i = 0; i < selectedSynName.size(); i++) {
        selectedSynName[i].getSynName() == expectedSelectedSynName[i];
    }
    REQUIRE(resultTable.getResultTable() == expectedResultTable);

}

TEST_CASE("Select Handler test 4: same synonyms appear multiple times in Select") {

    PQLPreprocessor preprocessor;
    string queryStr = "variable a; Select <a,a> ";// variable: m, n, x; constant: 1, 5
    Query query = preprocessor.preprocess(queryStr);
    SelectClause selectClause = query.getSelectClause();

    std::multimap<std::string, std::string> varTable = query.getSynonymTable();
    ResultTable resultTable = ResultTable();

    PKB pkb;
    testSelectSynPkb(pkb);

    SelectHandler selectHandler = SelectHandler(pkb);
    std::vector<Elem> selectedSynName = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name
    std::vector<std::string> expectedSelectedSynName = { "a", "a" };
    std::vector<std::vector<std::string>> expectedResultTable = {{ "m", "n", "x"}};
    std::vector<std::string> expectedSynList = { "a" };

    for (int i = 0; i < selectedSynName.size(); i++) {
        selectedSynName[i].getSynName() = expectedSelectedSynName[i];
    }
    REQUIRE(resultTable.getResultTable() == expectedResultTable);
    REQUIRE(resultTable.getSynList() == expectedSynList);
}

TEST_CASE("Select Handler test 5: select attribute") {
    PQLPreprocessor preprocessor;
    string queryStr = "assign a; Select a.stmt#";
    Query query = preprocessor.preprocess(queryStr);
    SelectClause selectClause = query.getSelectClause();
    std::multimap<std::string, std::string> varTable = query.getSynonymTable();
    ResultTable resultTable = ResultTable();

    PKB pkb;
    testSelectSynPkb(pkb);


    SelectHandler selectHandler = SelectHandler(pkb);
    std::vector<Elem> selectedElem = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name
    REQUIRE(selectedElem.size() == 1);
    REQUIRE(selectedElem[0].isElemSynonym() == false);
}
