#include "pkb/include/PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/tokenizer/PQLPreprocessor.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/model/Elem.h"
#include "TestUtility.h"
#include "catch.hpp"

using namespace std;

void testSelectSynPkb(PKB& pkb) {
    pkb.addAllVars(set<string>({ "x", "n", "m" }));
    pkb.addAllConsts(set<string>({ "1", "5" }));

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 2, 3})));
    stmts.insert(make_pair(KeywordsEnum::IF, set<int>({ 1 })));
    pkb.addAllStmts(stmts);

    unordered_map<string, set<Line>> assignPatterns;
    Line line2 = Line(2, vector<string>({ "n", "1", "+" }), IF);
    Line line3 = Line(3, vector<string>({ "m", "1", "-" }), IF);

    assignPatterns.insert(make_pair("n", set<Line>({ line2 })));
    assignPatterns.insert(make_pair("m", set<Line>({ line3 })));
    pkb.addAllAssignPatterns(assignPatterns);

    unordered_map<string, set<Line>> ifPatterns;
    Line line1 = Line(1, vector<string>({ "x", "5", ">" }), IF);
    ifPatterns.insert(make_pair("x", set<Line>({ line1 })));
    pkb.addAllIfPatterns(ifPatterns);

    // Line 1: if (x > 5) {
    // Line 2: n = n + 1 } else {
    // Line 3: m = m - 1}
}

std::set<string> testSelect(string queryStr) {
    PKB pkb;

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 1 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 2 })));
    stmts.insert(make_pair(KeywordsEnum::IF, set<int>({ 3 })));
    stmts.insert(make_pair(KeywordsEnum::PRINT, set<int>({ 4 })));
    stmts.insert(make_pair(KeywordsEnum::CALL, set<int>({ 5 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 6 })));
    pkb.addAllStmts(stmts);
    pkb.addAllFollows({ {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6} });

    pkb.addAllVars({ "x" });
    pkb.addAllConsts({ "1", "2" });
    pkb.addAllProcs({ "main", "foo" });
    PQLDriver driver = PQLDriver(pkb);
    set<string> retSet = driver.processPQL(queryStr);
    
    return retSet;

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

    unordered_map<KeywordsEnum, set<int>> stmts;
    stmts.insert(make_pair(KeywordsEnum::ASSIGN, set<int>({ 1, 2 })));
    stmts.insert(make_pair(KeywordsEnum::READ, set<int>({ 3, 7, 8 })));
    stmts.insert(make_pair(KeywordsEnum::IF, set<int>({ 4 })));
    stmts.insert(make_pair(KeywordsEnum::WHILE, set<int>({ 5 })));
    stmts.insert(make_pair(KeywordsEnum::CALL, set<int>({ 6 })));
    pkb.addAllStmts(stmts);

    pkb.addAllVars(set<string>({ "x", "y", "z" }));
    pkb.addAllConsts(set<string>({ "10", "11", "12", "13"}));


    SelectHandler selectHandler = SelectHandler(pkb);
    std::vector<Elem> selectedVarName = selectHandler.evalSelect(selectClause, varTable, resultTable);// update resultTable and return the synonym name

    set<std::string> retSet = resultTable.getSelectedResult(selectedVarName, pkb, false);
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

        set<std::string> retSet = resultTable.getSelectedResult(selectedVarName, pkb, false);
        REQUIRE(selectedVarName[0].getSynName() == "c");
        REQUIRE(retSet.size() == 4);
        REQUIRE(retSet.count("10") == 1);
        REQUIRE(retSet.count("11") == 1);
        REQUIRE(retSet.count("12") == 1);
        REQUIRE(retSet.count("13") == 1);

}

TEST_CASE("Select Handler test 3 single synonym") {
    std::set<string> retStr1 = testSelect("assign a; Select a");
    std::set<string> expected1 = {"1"};
    REQUIRE(retStr1 == expected1);

    std::set<string> retStr2 = testSelect("stmt s; Select s");
    std::set<string> expected2 = {"1", "2", "3", "4", "5", "6"};
    REQUIRE(retStr2 == expected2);

    std::set<string> retStr3 = testSelect("stmt s; Select s such that Follows(1,7)");
    std::set<string> expected3 = {};
    REQUIRE(retStr3 == expected3);
}

TEST_CASE("Select Handler test 4 single synonym attribute") {
    std::set<std::string> retStr1 = testSelect("assign a; Select a.stmt#");
    std::set<std::string> expected1 = { "1" };
    REQUIRE(retStr1 == expected1);

    std::set<std::string> retStr2 = testSelect("stmt s; Select s.stmt#");
    std::set<std::string> expected2 = { "1", "2", "3", "4", "5", "6" };
    REQUIRE(retStr2 == expected2);

    std::set<std::string> retStr3 = testSelect("stmt s; Select s.stmt# such that Follows(1,7)");
    std::set<std::string> expected3 = {};
    REQUIRE(retStr3 == expected3);
}

TEST_CASE("Select Handler test BOOLEAN") {
    std::set<std::string> retStr1 = testSelect("assign a; Select BOOLEAN");
    std::set<std::string> expected1 = { "TRUE" };
    REQUIRE(retStr1 == expected1);

    std::set<std::string> retStr2 = testSelect("Select BOOLEAN");
    std::set<std::string> expected2 = { "TRUE" };
    REQUIRE(retStr2 == expected2);

    std::set<std::string> retStr3 = testSelect("stmt s; Select BOOLEAN with s.stmt#=1");
    std::set<std::string> expected3 = { "TRUE" };
    REQUIRE(retStr3 == expected3);

    std::set<std::string> retStr4 = testSelect("stmt s; Select BOOLEAN with s.stmt#=7");
    std::set<std::string> expected4 = { "FALSE" };
    REQUIRE(retStr4 == expected4);

    std::set<std::string> retStr5 = testSelect("stmt s; Select BOOLEAN such that Follows(1,3)");
    std::set<std::string> expected5 = { "FALSE" };
    REQUIRE(retStr5 == expected5);

    std::set<std::string> retStr6 = testSelect("stmt BOOLEAN; Select BOOLEAN");
    std::set<std::string> expected6 = { "1", "2", "3", "4", "5", "6"};
    REQUIRE(retStr6 == expected6);
}

TEST_CASE("Select Handler test 5 multi synonyms") {
    std::set<std::string> retStr1 = testSelect("stmt s1, s2; Select <s1, s2> such that Follows(s1, s2)");
    std::set<std::string> expected1 = { "1 2", "2 3", "3 4", "4 5", "5 6"};
    REQUIRE(retStr1 == expected1);

    std::set<std::string> retStr2 = testSelect("stmt s1, s2; Select <s1, s2>");
    std::set<std::string> expected2 = { "1 1","1 2","1 3","1 4","1 5","1 6",
    "2 1","2 2","2 3","2 4","2 5","2 6",
    "3 1","3 2","3 3","3 4","3 5", "3 6",
    "4 1","4 2","4 3","4 4","4 5","4 6",
    "5 1","5 2","5 3","5 4", "5 5", "5 6",
    "6 1","6 2","6 3","6 4","6 5","6 6"};
    REQUIRE(retStr2 == expected2);

}

TEST_CASE("Select Handler test 6 multi synonyms with attribute") {
    std::set<std::string> retStr1 = testSelect("stmt s1, s2; Select <s1, s2.stmt#> such that Follows(s1, s2)");
    std::set<std::string> expected1 = { "1 2", "2 3", "3 4", "4 5", "5 6" };
    REQUIRE(retStr1 == expected1);

    std::set<std::string> retStr2 = testSelect("stmt s1, s2; Select <s1.stmt#, s2>");
    std::set<std::string> expected2 = { "1 1","1 2","1 3","1 4","1 5","1 6",
    "2 1","2 2","2 3","2 4","2 5","2 6",
    "3 1","3 2","3 3","3 4","3 5", "3 6",
    "4 1","4 2","4 3","4 4","4 5","4 6",
    "5 1","5 2","5 3","5 4", "5 5", "5 6",
    "6 1","6 2","6 3","6 4","6 5","6 6" };
    REQUIRE(retStr2 == expected2);

    std::set<std::string> retStr3 = testSelect("stmt s1, s2; Select <s1.stmt#> such that Follows(s1, s2)");
    std::set<std::string> expected3 = { "1", "2", "3", "4", "5" };
    REQUIRE(retStr1 == expected1);
}

TEST_CASE("Select Handler test: multiple synonyms") {

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
        selectedSynName[i].getSynName() = expectedSelectedSynName[i];
    }
    REQUIRE(resultTable.getResultTable() == expectedResultTable);

}

TEST_CASE("Select Handler test: same synonyms appear multiple times in Select") {

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

TEST_CASE("Select Handler test: select attribute") {
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
