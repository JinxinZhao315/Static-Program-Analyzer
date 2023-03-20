#include "pkb/include/PKB.h"
#include "QPS/include/evaluator/PQLEvaluator.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/evaluator/FollowsHandler.h"
#include "QPS/include/PQLDriver.h"
#include "source_processor/include/SourceProcessor.h"

#include "catch.hpp"
using namespace std;

void spDriver(std::string filename, PKB &pkb) {
    SourceProcessor sourceProcessor = SourceProcessor();
    sourceProcessor.parseProgram(filename);
    sourceProcessor.storeDataInPKB(&pkb);
}
set<string> qpsDriver(std::string queryStr, PKB& pkb) {
    PQLDriver pqlDriver = PQLDriver(pkb);
    set<string> result = pqlDriver.processPQL(queryStr);
    return result;
}

set<string> testDriver(string filename, string queryStr) {
    PKB pkb;
    spDriver(filename, pkb);
    return qpsDriver(queryStr, pkb);
}

//string source_sample1 = "../../../../Tests15/source-sample1.txt";
//string source_sample2 = "../../../../Tests15/source-sample2.txt";
//string source_sample3 = "../../../../Tests15/source-sample3.txt";
//string source_general = "../../../../Tests15/source-general.txt";
//string source_follows = "../../../../Tests15/source-follows.txt";
//string source_parent = "../../../../Tests15/source-parent.txt";
//string source7 = "../../../../Tests15/source-7.txt";
//string uses_modifies = "../../../../Tests15/source-usesmodifies.txt";
//string uses_modifies2 = "../../../../Tests15/source-usesmodifies2.txt";
//string source_with = "../../../../Tests15/with.txt";

//string sample_source2 = "../../../../Tests15/Sample_source2.txt";
//string source1_filename = "../../../../Tests15/source1.txt";
//string source2_filename = "../../../../Tests15/source2.txt";
//string source3_filename = "../../../../Tests15/source3.txt";
//string source4_filename = "../../../../Tests15/source4.txt";
//string source7_filename = "../../../../Tests15/source7.txt";

//TEST_CASE("Overall test : source-usesmodifies.txt 1") {
//    string filename = uses_modifies;
//    string queryStr = "stmt s; Select s such that Uses(s, \"a\")";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "6" };
//    REQUIRE(result == expectedResult);
//}

#if __APPLE__
    string source_sample1 = "../../../../../../../Tests15/source-sample1.txt";
    string source_sample2 = "../../../../../../../Tests15/source-sample2.txt";
    string source_sample3 = "../../../../../../../Tests15/source-sample3.txt";
    string source_general = "../../../../../../../Tests15/source-general.txt";
    string source_follows = "../../../../../../../Tests15/source-follows.txt";
    string source_parent = "../../../../../../../Tests15/source-parent.txt";
    string source7 = "../../../../../../../Tests15/source-7.txt";
    string uses_modifies = "../../../../../../../Tests15/source-usesmodifies.txt";
    string uses_modifies2 = "../../../../../../../Tests15/source-usesmodifies2.txt";
    string source_with = "../../../../../../../Tests15/with.txt";
#elif _WIN32
    string source_sample1 = "./Team15/Tests15/source-sample1.txt";
    string source_sample2 = "./Team15/Tests15/source-sample2.txt";
    string source_sample3 = "./Team15/Tests15/source-sample3.txt";
    string source_general = "./Team15/Tests15/source-general.txt";
    string source_follows = "./Team15/Tests15/source-follows.txt";
    string source_parent = "./Team15/Tests15/source-parent.txt";
    string source7 = "./Team15/Tests15/source-7.txt";
    string uses_modifies = "./Team15/Tests15/source-usesmodifies.txt";
    string uses_modifies2 = "./Team15/Tests15/source-usesmodifies2.txt";
    string source_with = "./Team15/Tests15/with.txt";
#endif

TEST_CASE("Overall test: temp") {
    string filename = source_with;
    string queryStr = "print p; Select p such that Uses(p, _) with p.varName = \"c\"";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "5" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source-sample1.txt 6") {
    string filename = source_sample1;
    string queryStr = "assign a1, a2, a3; stmt s1, s2, s3; \
        variable v1, v2, v3;Select <s1, s2, v2> such that Uses(s3, v1) \
        and Modifies(s3, \"x\") and Follows(s1, s2) and Parent(s3, s1) and Uses(s2, v1)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "TRUE" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 1") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "variable v; Select v";

    PKB pkb;
    spDriver(filename, pkb);
    set<string> result = qpsDriver(queryStr, pkb);

    set<string> expectedResult = { "v", "w", "x", "y", "z", "a", "b", "c", "d", "e", "f", "g" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 2") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "variable v; Select v such that Modifies(14, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "w" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 3") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "read re; Select re such that Modifies(re, \"g\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "12" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 4") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "variable v; Select v such that Uses(14, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "a", "b", "c" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 5") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "print pr; Select pr such that Uses(pr, \"x\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "18" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 6") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; Select s such that Follows(16, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "17" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 7") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; Select s such that Follows(s, 15)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "14" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 8") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "read re; variable v; Select v such that Modifies(re, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "g" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 9") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "print pr; variable v; Select v such that Uses(pr, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "x" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 10 SyntaxError") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "variable v; Select v;";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "SyntaxError" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 11 SemanticError") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "print p; Select p pattern p(_,_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "SemanticError" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 12 SemanticError") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; Select s pattern s(_,_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "SemanticError" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 13") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; procedure p; variable v; Select p such that Uses(p, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "proc1" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 14") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; procedure p; variable v; read r; Select r such that Uses(\"proc1\", v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "12" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 15") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "while w; Select w pattern w (_,_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 16") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; procedure p; variable v; read r; Select r such that Modifies(\"proc1\", \"a\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "12" };
    REQUIRE(result == expectedResult);

    queryStr = "stmt s; procedure p; variable v; read r; Select r such that Modifies(p, v)";

    result = testDriver(filename, queryStr);
    expectedResult = { "12" };
    REQUIRE(result == expectedResult);
}



TEST_CASE("Overall test : source1.txt 17 Select Multiple synonyms") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "assign a1, a2; Select <a1, a2> such that Follows(a1, a2)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {
        "1 2", "2 3", "3 4", "4 5", "5 6", "6 7",
        "7 8", "8 9", "9 10", "10 11",
        "13 14", "14 15", "15 16", "16 17"};
    REQUIRE(result == expectedResult);

    queryStr = "assign a1, a2; Select <a1> such that Follows(a1, a2)";

    result = testDriver(filename, queryStr);
    expectedResult = { "1", "2", "3", "4", "5", "6", "7", "8",
        "9", "10", "13", "14", "15", "16"};
    REQUIRE(result == expectedResult);

    queryStr = "assign a1, a2; Select <a1, a2> such that Parent(a1, a2)";

    result = testDriver(filename, queryStr);
    expectedResult = {};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 18 Select BOOLEAN") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "assign a1, a2; Select BOOLEAN such that Follows(a1, a2)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"TRUE"};
    REQUIRE(result == expectedResult);

    queryStr = "assign a1, a2; Select BOOLEAN such that Parent(a1, a2)";

    result = testDriver(filename, queryStr);
    expectedResult = {"FALSE"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 19 Select attribute") {
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "procedure p; read r; print pri; constant c; Select p.procName";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "proc1" };
    REQUIRE(result == expectedResult);

    queryStr = "procedure p; read r; print pri; constant c; Select r.stmt#";

    result = testDriver(filename, queryStr);
    expectedResult = { "12" };
    REQUIRE(result == expectedResult);

    queryStr = "procedure p; read r; print pri; constant c; Select c.value";

    result = testDriver(filename, queryStr);
    expectedResult = { "0", "1", "2", "3", "4", "5", "6"};
    REQUIRE(result == expectedResult);

    queryStr = "procedure p; read r; print pri; constant c; Select r.varName";

    result = testDriver(filename, queryStr);
    expectedResult = { "g" };
    REQUIRE(result == expectedResult);

    queryStr = "procedure p; read r; print pri; constant c; Select pri.varName";

    result = testDriver(filename, queryStr);
    expectedResult = { "x" };
    REQUIRE(result == expectedResult);
}






















//TEST_CASE("Overall test : source2.txt 1") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//    string queryStr = "procedure p; Select p";
//
//    PKB pkb;
//    spDriver(filename, pkb);
//    set<string> result = qpsDriver(queryStr, pkb);
//
//    set<string> expectedResult = { "proc1", "proc2" };
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 2") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//    string queryStr = "call cl; Select cl such that Follows(19, cl)";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "21" };
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 3") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//    string queryStr = "call cl; Select cl such that Follows* (2, cl)";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "21" };
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 4") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//    string queryStr = "if i; Select i such that Follows(12, i)";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "13" };
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 5") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//    string queryStr = "while w; Select w such that Follows(18, w)";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "19" };
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 6") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//    string queryStr = "constant c; Select c";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 7") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//
//    set<string> result = testDriver(filename, "assign a; Select a pattern a(\"w\", _\"b\"_)");
//    set<string> expectedResult = { "14", "22" };
//    REQUIRE(result == expectedResult);
//
//    set<string> result1 = testDriver(filename, "assign a; Select a pattern a(\"w\", \"b\")");
//    set<string> expectedResult1 = { };
//    REQUIRE(result1 == expectedResult1);
//
//    set<string> result2 = testDriver(filename, "assign a; Select a pattern a(_, \"0\")");
//    set<string> expectedResult2 = {"1", "2", "3", "4", "5", "18"};
//    REQUIRE(result2 == expectedResult2);
//
//    set<string> result3 = testDriver(filename, "assign a; variable v; Select v pattern a(v, \"0\")");
//    set<string> expectedResult3 = { "v", "w", "x", "y", "z", "count" };
//    REQUIRE(result3 == expectedResult3);
//
//}
//
//TEST_CASE("Overall test : source2.txt 8") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//    string queryStr = "assign a; Select a pattern a (_, _\" a\"_)";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "12", "14", "15", "16", "17" };
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 9") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//    string queryStr = "assign a; Select a pattern a (_, _\"c \"_)";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "12", "14", "15", "16", "17", "22"};
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 10") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//    string queryStr = "assign a; Select a pattern a(\"count\", _\"count\"_)";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "20" };
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 11") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//    string queryStr = "stmt s; Select s such that Modifies(s, \"y\")";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "4", "13", "16" };
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 12") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//    string queryStr = "stmt s; Select s such that Uses(s, \"e\")";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "13", "17" , "23"};
//    REQUIRE(result == expectedResult);
//}
//
//// Multiple clauses
//TEST_CASE("Overall test : source2.txt 13") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//
//    string queryStr = "assign a; Select a such that Modifies (a, \"y\") pattern a (_, _\"a\"_)";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = {"16"};
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 14") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//
//    string queryStr = "assign a1, a2; Select a1 such that Follows(a1,a2) pattern a2 (_, _\"e\"_)";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = {"22"};
//    REQUIRE(result == expectedResult);
//}
//
//TEST_CASE("Overall test : source2.txt 15") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//
//    string queryStr = "while w; Select w pattern w (_,_)";
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = {"19"};
//    REQUIRE(result == expectedResult);
//
//    string queryStr1 = "if i; Select i pattern i (_,_,_)";
//    set<string> result1 = testDriver(filename, queryStr1);
//    set<string> expectedResult1 = {"13"};
//    REQUIRE(result1 == expectedResult1);
//}
//
//TEST_CASE("Overall test : source2.txt 16") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//
//    string queryStr = "while w; variable v; Select v pattern w (v,_)";
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = {"count"};
//    REQUIRE(result == expectedResult);
//
//    string queryStr1 = "if i; variable v; Select v pattern i (v,_,_)";
//    set<string> result1 = testDriver(filename, queryStr1);
//    set<string> expectedResult1 = {"v"};
//    REQUIRE(result1 == expectedResult1);
//}
//
//TEST_CASE("Overall test : source2.txt 17") {
//    // Enter source of SIMPLE code
//    string filename = source2_filename;
//
//    string queryStr = "while w; Select w pattern w (\"count\",_)";
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = {"19"};
//    REQUIRE(result == expectedResult);
//
//    string queryStr1 = "if i; Select i pattern i (\"v\",_,_)";
//    set<string> result1 = testDriver(filename, queryStr1);
//    set<string> expectedResult1 = {"13"};
//    REQUIRE(result1 == expectedResult1);
//}





TEST_CASE("Overall test : source3.txt 1") {
    // Enter source of SIMPLE code
    string filename =  source_follows;
    string queryStr = "stmt s; Select s such that Follows* (9, s)";

    PKB pkb;
    spDriver(filename, pkb);
    set<string> result = qpsDriver(queryStr, pkb);

    set<string> expectedResult = { "10", "11", "17", "18"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source3.txt 2") {
    // Enter source of SIMPLE code
    string filename =  source_follows;
    string queryStr = "stmt s; Select s such that Follows* (s, 15)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "13", "14" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source3.txt 3") {
    // Enter source of SIMPLE code
    string filename =  source_follows;
    string queryStr = "stmt s; Select s such that Parent(11, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "12" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source3.txt 4") {
    // Enter source of SIMPLE code
    string filename =  source_follows;
    string queryStr = "stmt s; Select s such that Parent(12, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "13", "14", "15", "16"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source3.txt 5") {
    // Enter source of SIMPLE code
    string filename =  source_follows;
    string queryStr = "stmt s; Select s such that Parent(s, 14)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "12" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source3.txt 6") {
    // Enter source of SIMPLE code
    string filename =  source_follows;
    string queryStr = "stmt s; Select s such that Parent(s, 12)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "11" };
    REQUIRE(result == expectedResult);
}

// Multiple clauses
TEST_CASE("Overall test : source3.txt 7") {
    // Enter source of SIMPLE code
    string filename =  source_follows;

    string queryStr1 = "assign a; variable v; Select v such that Modifies(a,v) pattern a (_,_\"e\"_)";
    set<string> result1 = testDriver(filename, queryStr1);
    set<string> expectedResult1 = { "c", "x", "y" };
    REQUIRE(result1 == expectedResult1);

    string queryStr2 = "assign a; variable v; Select v such that Modifies(a,v) pattern a (_,_\"blah\"_)";
    set<string> result2 = testDriver(filename, queryStr2);
    set<string> expectedResult2 = { };
    REQUIRE(result2 == expectedResult2);
}

TEST_CASE("Overall test : source3.txt 8") {
    // Enter source of SIMPLE code
    string filename = source_follows;

    string queryStr = "while w; Select w pattern w (\"count\",_)";
    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"11"};
    REQUIRE(result == expectedResult);

    string queryStr1 = "if i; Select i pattern i (\"a\",_,_)";
    set<string> result1 = testDriver(filename, queryStr1);
    set<string> expectedResult1 = {"12"};
    REQUIRE(result1 == expectedResult1);
}


TEST_CASE("Overall test : source4.txt 1") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent* (5, s)";

    PKB pkb;
    spDriver(filename, pkb);
    set<string> result = qpsDriver(queryStr, pkb);

    set<string> expectedResult = { "6", "7", "8", "9", "10", "11", "12", "13"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 2") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent* (s, 11)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "4", "5", "6", "7", "10" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 3") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent* (6, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "7", "8", "9", "10", "11", "12", "13" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 4") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent* (s, 12)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "4", "5", "6", "7", "10" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 5") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent* (7, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "8", "9", "10", "11", "12" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 6") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent* (s, 9)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "4", "5", "6", "7" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 7") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent* (8, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 8") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent* (s, 8)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "4", "5", "6", "7" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 9") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent* (12, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 10") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent* (s, 7)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "4", "5", "6" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source4.txt 11") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent* (s, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source4.txt 12") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Parent (s, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source4.txt 13") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Follows (s, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source4.txt 14") {
    // Enter source of SIMPLE code
    string filename = source_parent;
    string queryStr = "stmt s; Select s such that Follows* (s, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source4.txt 15") {
    // Enter source of SIMPLE code
    string filename = source_parent;

    string queryStr = "while w; Select w pattern w (\"b\",_)";
    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"5"};
    REQUIRE(result == expectedResult);

    string queryStr1 = "if i; Select i pattern i (\"b\",_,_)";
    set<string> result1 = testDriver(filename, queryStr1);
    set<string> expectedResult1 = {"7", "10"};
    REQUIRE(result1 == expectedResult1);
}


TEST_CASE("Overall test : source7.txt 1") {
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Uses(p, \"y\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"Loid", "Anya", "Yor"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 2") {
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Modifies(p, \"x\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"Loid", "Anya", "Yor"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 3") {
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls(p, p)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 4") {
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls*(\"Loid\", \"Loid\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 5") {
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls*(\"Loid\", p)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"Anya", "Yor"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 6") {
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls(\"Loid\", p)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "Anya" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 7") {
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p,q; Select q such that Calls(p, q)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "Anya", "Yor" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 8") {
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls(p, _)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "Loid", "Anya"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 9") {
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls(_, p)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "Anya", "Yor" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 10") {
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls*(_, _)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "Loid","Anya", "Yor" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source-ifwhile.txt 1") {
    string filename = "../../../../Tests15/source-ifwhile.txt";
    string queryStr = "while w; Select w such that Parent*(w, 10) and Uses(w, \"x\") and Follows(6, w) pattern w (\"x\", _)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "8" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source-ifwhile.txt 2") {
    string filename = "../../../../Tests15/source-ifwhile.txt";
    string queryStr = "if i; Select i such that Parent(i, 11) and Modifies(i, \"x\") and Follows(i, 12) pattern i (\"x\", _, _)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "9" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source-sample1.txt") {
    string filename = source_sample1;
    string queryStr = "stmt s; Select s such that Modifies(s, \"i\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "3", "4", "11", "12", "13", "14", "17" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source-sample1.txt 2") {
    string filename = source_sample1;
    string queryStr = "stmt s; Select s such that Uses(s, \"x\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"4","5","6","7","8","9","10","12","13","16","18","19","21","22","23","24"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source-sample3.txt 3") {
    string filename = source_sample1;
    string queryStr = "stmt s; Select BOOLEAN such that Uses(\"main\", \"flag\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"TRUE" };
    REQUIRE(result == expectedResult);
}

//TEST_CASE("Overall test : source-sample1.txt 6") {
//    string filename = source_sample1;
//    string queryStr = "assign a1, a2, a3; stmt s1, s2, s3; variable v1, v2, v3;Select <s1, s2, v2> such that Uses(s3, v1) and Modifies(s3, \"x\") and Follows(s1, s2) and Parent(s3, s1) and Uses(s2, v1)";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "TRUE" };
//    REQUIRE(result == expectedResult);
//}
