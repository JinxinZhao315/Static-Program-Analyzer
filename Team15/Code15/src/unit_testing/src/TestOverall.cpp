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

string sample_source2 = "../../../../Tests15/Sample_source2.txt";
string source1_filename = "../../../../Tests15/source1.txt";
string source2_filename = "../../../../Tests15/source2.txt";
string source3_filename = "../../../../Tests15/source3.txt";
string source4_filename = "../../../../Tests15/source4.txt";

TEST_CASE("Overall test : Sample_source2.txt 0") {
    // Enter source of SIMPLE code
    string filename = sample_source2;
    string queryStr = "constant c; Select c";

    set<string> result = testDriver(filename, queryStr);

    set<string> expectedResult = { "2", "3", "5" };
    REQUIRE(result == expectedResult);
}







TEST_CASE("Overall test : source1.txt 1") {
    // Enter source of SIMPLE code
    string filename = source1_filename;
    string queryStr = "variable v; Select v";

    PKB pkb;
    spDriver(filename, pkb);
    set<string> result = qpsDriver(queryStr, pkb);

    set<string> expectedResult = { "v", "w", "x", "y", "z", "a", "b", "c", "d", "e", "f", "g" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 2") {
    // Enter source of SIMPLE code
    string filename = source1_filename;
    string queryStr = "variable v; Select v such that Modifies(14, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "w" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 3") {
    // Enter source of SIMPLE code
    string filename = source1_filename;
    string queryStr = "read re; Select re such that Modifies(re, \"g\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "12" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 4") {
    // Enter source of SIMPLE code
    string filename = source1_filename;
    string queryStr = "variable v; Select v such that Uses(14, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "a", "b", "c" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 5") {
    // Enter source of SIMPLE code
    string filename = source1_filename;
    string queryStr = "stmt s; Select s such that Modifies(s, \"y\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "16" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 6") {
    // Enter source of SIMPLE code
    string filename = source1_filename;
    string queryStr = "stmt s; Select s such that Uses(s, \"e\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "17" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 7") {
    // Enter source of SIMPLE code
    string filename = source1_filename;
    string queryStr = "print pr; Select pr such that Uses(pr, \"x\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "18" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 8") {
    // Enter source of SIMPLE code
    string filename = source1_filename;
    string queryStr = "stmt s; Select s such that Follows(16, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "17" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 9") {
    // Enter source of SIMPLE code
    string filename = source1_filename;
    string queryStr = "stmt s; Select s such that Follows(s, 15)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "14" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 10") {
    // Enter source of SIMPLE code
    string filename = source1_filename;
    string queryStr = "read re; variable v; Select v such that Modifies(re, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "g" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 11") {
    // Enter source of SIMPLE code
    string filename = source1_filename;
    string queryStr = "print pr; variable v; Select v such that Uses(pr, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "x" };
    REQUIRE(result == expectedResult);
}









TEST_CASE("Overall test : source2.txt 1") {
    // Enter source of SIMPLE code
    string filename = source2_filename;
    string queryStr = "procedure p; Select p";

    PKB pkb;
    spDriver(filename, pkb);
    set<string> result = qpsDriver(queryStr, pkb);

    set<string> expectedResult = { "proc1", "proc2" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source2.txt 2") {
    // Enter source of SIMPLE code
    string filename = source2_filename;
    string queryStr = "call cl; Select cl such that Follows(19, cl)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "21" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source2.txt 3") {
    // Enter source of SIMPLE code
    string filename = source2_filename;
    string queryStr = "call cl; Select cl such that Follows* (2, cl)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "21" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source2.txt 4") {
    // Enter source of SIMPLE code
    string filename = source2_filename;
    string queryStr = "if i; Select i such that Follows(12, i)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "13" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source2.txt 5") {
    // Enter source of SIMPLE code
    string filename = source2_filename;
    string queryStr = "while w; Select w such that Follows(18, w)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "19" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source2.txt 6") {
    // Enter source of SIMPLE code
    string filename = source2_filename;
    string queryStr = "constant c; Select c";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source2.txt 7") {
    // Enter source of SIMPLE code
    string filename = source2_filename;
    string queryStr = "assign a; Select a pattern a(\"w\", _\"b + c\"_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "14", "22" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source2.txt 8") {
    // Enter source of SIMPLE code
    string filename = source2_filename;
    string queryStr = "assign a; Select a pattern a(_, _\"a * b\"_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "15" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source2.txt 9") {
    // Enter source of SIMPLE code
    string filename = source2_filename;
    string queryStr = "assign a; Select a pattern a(_, _\"c * d\"_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "none" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source2.txt 10") {
    // Enter source of SIMPLE code
    string filename = source2_filename;
    string queryStr = "assign a; Select a pattern a(\"count\", \"count\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "none" };
    REQUIRE(result == expectedResult);
}












TEST_CASE("Overall test : source3.txt 1") {
    // Enter source of SIMPLE code
    string filename =  source3_filename;
    string queryStr = "stmt s; Select s such that Follows* (9, s)";

    PKB pkb;
    spDriver(filename, pkb);
    set<string> result = qpsDriver(queryStr, pkb);

    set<string> expectedResult = { "10", "11", "17" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source3.txt 2") {
    // Enter source of SIMPLE code
    string filename =  source3_filename;
    string queryStr = "stmt s; Select s such that Follows* (s, 15)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "13", "14" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source3.txt 3") {
    // Enter source of SIMPLE code
    string filename =  source3_filename;
    string queryStr = "stmt s; Select s such that Parent(11, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "12" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source3.txt 4") {
    // Enter source of SIMPLE code
    string filename =  source3_filename;
    string queryStr = "stmt s; Select s such that Parent(12, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "13", "14", "15"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source3.txt 5") {
    // Enter source of SIMPLE code
    string filename =  source3_filename;
    string queryStr = "stmt s; Select s such that Parent(s, 14)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "12" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source3.txt 6") {
    // Enter source of SIMPLE code
    string filename =  source3_filename;
    string queryStr = "stmt s; Select s such that Parent(s, 12)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "11" };
    REQUIRE(result == expectedResult);
}










TEST_CASE("Overall test : source4.txt 1") {
    // Enter source of SIMPLE code
    string filename = source4_filename;
    string queryStr = "stmt s; Select s such that Parent* (5, s)";

    PKB pkb;
    spDriver(filename, pkb);
    set<string> result = qpsDriver(queryStr, pkb);

    set<string> expectedResult = { "6", "7", "8", "9", "10", "11", "12", "13"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 2") {
    // Enter source of SIMPLE code
    string filename = source4_filename;
    string queryStr = "stmt s; Select s such that Parent* (s, 11)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "4", "5", "6", "7", "10" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 3") {
    // Enter source of SIMPLE code
    string filename = source4_filename;
    string queryStr = "stmt s; Select s such that Parent* (6, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "7", "8", "9", "10", "11", "12", "13" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 4") {
    // Enter source of SIMPLE code
    string filename = source4_filename;
    string queryStr = "stmt s; Select s such that Parent* (s, 12)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "4", "5", "6", "7", "10" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 5") {
    // Enter source of SIMPLE code
    string filename = source4_filename;
    string queryStr = "stmt s; Select s such that Parent* (7, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "8", "9", "10", "11", "12" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 6") {
    // Enter source of SIMPLE code
    string filename = source4_filename;
    string queryStr = "stmt s; Select s such that Parent* (s, 9)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "4", "5", "6", "7" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 7") {
    // Enter source of SIMPLE code
    string filename = source4_filename;
    string queryStr = "stmt s; Select s such that Parent* (8, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "none" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 8") {
    // Enter source of SIMPLE code
    string filename = source4_filename;
    string queryStr = "stmt s; Select s such that Parent* (s, 8)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "4", "5", "6", "7" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 9") {
    // Enter source of SIMPLE code
    string filename = source4_filename;
    string queryStr = "stmt s; Select s such that Parent* (12, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "none" };
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source4.txt 10") {
    // Enter source of SIMPLE code
    string filename = source4_filename;
    string queryStr = "stmt s; Select s such that Parent* (s, 7)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "4", "5", "6" };
    REQUIRE(result == expectedResult);
}













