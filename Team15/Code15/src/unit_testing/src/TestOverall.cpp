#include <utility>

#include "pkb/include/PKB.h"
#include "qps/include/evaluator/PQLEvaluator.h"
#include "qps/include/model/Result.h"
#include "qps/include/model/ResultTable.h"
#include "qps/include/PQLDriver.h"
#include "sp/include/SourceProcessor.h"

#include "catch.hpp"
using namespace std;

void spDriver(std::string filename, PKB &pkb)
{
    auto sourceProcessor = SourceProcessor();
    sourceProcessor.parseProgram(std::move(filename), &pkb);
    sourceProcessor.storeDataInPKB(&pkb);
}
set<string> qpsDriver(std::string queryStr, PKB &pkb)
{
    PQLDriver pqlDriver = PQLDriver(pkb);
    set<string> result = pqlDriver.processPQL(std::move(queryStr));
    return result;
}

set<string> testDriver(string filename, string queryStr)
{
    PKB pkb;
    spDriver(std::move(filename), pkb);
    return qpsDriver(std::move(queryStr), pkb);
}

#if __APPLE__
string source_sample1 = "../../../../Tests15/local_test/source-sample1.txt";
string source_sample2 = "../../../../Tests15/local_test/source-sample2.txt";
string source_sample3 = "../../../../Tests15/local_test/source-sample3.txt";
string source_general = "../../../../Tests15/local_test/source-general.txt";
string source_follows = "../../../../Tests15/local_test/source-follows.txt";
string source_parent = "../../../../Tests15/local_test/source-parent.txt";
string source7 = "../../../../Tests15/local_test/source-7.txt";
string uses_modifies = "../../../../Tests15/local_test/source-usesmodifies.txt";
string source_with = "../../../../Tests15/local_test/with.txt";
string source_ifwhile = "../../../../Tests15/local_test/source-ifwhile.txt";
string source_optimization = "../../../../Tests15/local_test/source-optimization.txt";
string source_affects = "../../../../Tests15/local_test/source-affects.txt";
string source_invalid1 = "../../../../Tests15/g_invalid/1_source.txt";
#elif _WIN32
string source_sample1 = "../../../../../../Tests15/local_test/source-sample1.txt";
string source_sample2 = "../../../../../../Tests15/local_test/source-sample2.txt";
string source_sample3 = "../../../../../../Tests15/local_test/source-sample3.txt";
string source_general = "../../../../../../Tests15/local_test/source-general.txt";
string source_follows = "../../../../../../Tests15/local_test/source-follows.txt";
string source_parent = "../../../../../../Tests15/local_test/source-parent.txt";
string source7 = "../../../../../../Tests15/local_test/source-7.txt";
string uses_modifies = "../../../../../../Tests15/local_test/source-usesmodifies.txt";
string source_with = "../../../../../../Tests15/local_test/with.txt";
string source_ifwhile = "../../../../../../Tests15/local_test/source-ifwhile.txt";
string source_optimization = "../../../../../../Tests15/local_test/source-optimization.txt";
string source_affects = "../../../../../../Tests15/local_test/source-affects.txt";
string source_invalid1 = "../../../../../../Tests15/g_invalid/1_source.txt";
string source_g8 = "../../../../../../Tests15/g/8_source.txt";
string source_12 = "../../../../../../Tests15/g2/12_source.txt";
#endif

TEST_CASE("Overall test : source-usesmodifies.txt 1")
{
    string filename = uses_modifies;
    string queryStr = "stmt s; Select s such that Uses(s, \"a\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"2", "3", "4", "5", "7", "10", "11"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test: temp")
{
    string filename = source_with;
    string queryStr = "print p; Select p such that Uses(p, _) with p.varName = \"c\"";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"5"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source-sample1.txt 6")
{
    string filename = source_sample1;
    string queryStr = "assign a1, a2, a3; stmt s1, s2, s3; \
        variable v1, v2, v3;Select <s1, s2, v2> such that Uses(s3, v1) \
        and Modifies(s3, \"x\") and Follows(s1, s2) and Parent(s3, s1) and Uses(s2, v1)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {
        "10 11 i", "10 11 x", "10 11 y", "10 11 z", "14 18 i", "14 18 x", "14 18 y",
        "14 18 z", "15 16 i", "15 16 x", "15 16 y", "15 16 z", "16 17 i", "16 17 x",
        "16 17 y", "16 17 z", "18 19 i", "18 19 x", "18 19 y", "18 19 z", "5 6 i", "5 6 x",
        "5 6 y", "5 6 z", "6 9 i", "6 9 x", "6 9 y", "6 9 z", "9 10 i", "9 10 x", "9 10 y", "9 10 z"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 1")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "variable v; Select v";

    PKB pkb;
    spDriver(filename, pkb);
    set<string> result = qpsDriver(queryStr, pkb);

    set<string> expectedResult = {"v", "w", "x", "y", "z", "a", "b", "c", "d", "e", "f", "g"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 2")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "variable v; Select v such that Modifies(14, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"w"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 3")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "read re; Select re such that Modifies(re, \"g\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"12"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 4")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "variable v; Select v such that Uses(14, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"a", "b", "c"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 5")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "print pr; Select pr such that Uses(pr, \"x\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"18"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 6")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; Select s such that Follows(16, s)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"17"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 7")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; Select s such that Follows(s, 15)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"14"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 8")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "read re; variable v; Select v such that Modifies(re, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"g"};
    REQUIRE(result == expectedResult);
}
TEST_CASE("Overall test : source1.txt 9")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "print pr; variable v; Select v such that Uses(pr, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"x"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 10 SyntaxError")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "variable v; Select v;";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"SyntaxError"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 11 SemanticError")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "print p; Select p pattern p(_,_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"SemanticError"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 12 SemanticError")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; Select s pattern s(_,_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"SemanticError"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 13")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; procedure p; variable v; Select p such that Uses(p, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"proc1"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 14")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; procedure p; variable v; read r; Select r such that Uses(\"proc1\", v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"12"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 15")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "while w; Select w pattern w (_,_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 16")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "stmt s; procedure p; variable v; read r; Select r such that Modifies(\"proc1\", \"a\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"12"};
    REQUIRE(result == expectedResult);

    queryStr = "stmt s; procedure p; variable v; read r; Select r such that Modifies(p, v)";

    result = testDriver(filename, queryStr);
    expectedResult = {"12"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 17 Select Multiple synonyms")
{
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
    expectedResult = {"1", "2", "3", "4", "5", "6", "7", "8",
                      "9", "10", "13", "14", "15", "16"};
    REQUIRE(result == expectedResult);

    queryStr = "assign a1, a2; Select <a1, a2> such that Parent(a1, a2)";

    result = testDriver(filename, queryStr);
    expectedResult = {};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source1.txt 18 Select BOOLEAN")
{
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

TEST_CASE("Overall test : source1.txt 19 Select attribute")
{
    // Enter source of SIMPLE code
    string filename = source_general;
    string queryStr = "procedure p; read r; print pri; constant c; Select p.procName";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"proc1"};
    REQUIRE(result == expectedResult);

    queryStr = "procedure p; read r; print pri; constant c; Select r.stmt#";

    result = testDriver(filename, queryStr);
    expectedResult = {"12"};
    REQUIRE(result == expectedResult);

    queryStr = "procedure p; read r; print pri; constant c; Select c.value";

    result = testDriver(filename, queryStr);
    expectedResult = {"0", "1", "2", "3", "4", "5", "6"};
    REQUIRE(result == expectedResult);

    queryStr = "procedure p; read r; print pri; constant c; Select r.varName";

    result = testDriver(filename, queryStr);
    expectedResult = {"g"};
    REQUIRE(result == expectedResult);

    queryStr = "procedure p; read r; print pri; constant c; Select pri.varName";

    result = testDriver(filename, queryStr);
    expectedResult = {"x"};
    REQUIRE(result == expectedResult);
}




//TEST_CASE("Overall test : source-stresstest 1")
//{
//    string filename = source_stresstest;
//    string queryStr = "stmt s, s2; Select s such that Follows(s, s2)";
//    PKB pkb;
//    spDriver(filename, pkb);
//
//    string queryStr2 = "assign a1, a2, a3; stmt s1, s2, s3, s4, s5, s6, s7; variable v1, v2, v3;\
//        Select <s1, s2, v2> such that Follows*(s3, s2) and Uses(s3, v1) \
//        and Modifies(s3, \"x\") and Follows*(s1, s3) and Parent*(s4, s5) and Parent*(s6, s7) and Uses(s2, v1)";
//    result = qpsDriver(queryStr2, pkb);
//
//    string queryStr3 = "stmt s1, s2; Select <s1, s2> such that Next*(s1, s2)";
//    result = qpsDriver(queryStr3, pkb);
//}

TEST_CASE("Overall test : source3.txt 1")
{
    // Enter source of SIMPLE code
    PKB pkb;
    string filename = source_follows;
    string queryStr = "stmt s; Select s such that Follows* (9, s)";
    set<string> result = qpsDriver(queryStr, pkb);
}
TEST_CASE("Overall test : source7.txt 2")
{
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Modifies(p, \"x\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"Loid", "Anya", "Yor"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 3")
{
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls(p, p)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 4")
{
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls*(\"Loid\", \"Loid\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 5")
{
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls*(\"Loid\", p)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"Anya", "Yor"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 6")
{
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls(\"Loid\", p)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"Anya"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 7")
{
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p,q; Select q such that Calls(p, q)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"Anya", "Yor"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 8")
{
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls(p, _)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"Loid", "Anya"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 9")
{
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls(_, p)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"Anya", "Yor"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source7.txt 10")
{
    // Enter source of SIMPLE code
    string filename = source7;
    string queryStr = "stmt s; procedure p; Select p such that Calls*(_, _)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"Loid", "Anya", "Yor"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source-ifwhile.txt 1")
{
    string filename = source_ifwhile;
    string queryStr = "while w; Select w such that Parent*(w, 10) and Uses(w, \"x\") and Follows(6, w) pattern w (\"x\", _)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"8"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source-ifwhile.txt 2")
{
    string filename = source_ifwhile;
    string queryStr = "if i; Select i such that Parent(i, 11) and Modifies(i, \"x\") and Follows(i, 12) pattern i (\"x\", _, _)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"9"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source-sample1.txt")
{
    string filename = source_sample1;
    string queryStr = "stmt s; Select s such that Modifies(s, \"i\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"3", "4", "11", "12", "13", "14", "17"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : source-sample1.txt 2")
{
    string filename = source_sample1;
    string queryStr = "stmt s; Select s such that Uses(s, \"x\")";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = {"4", "5", "6", "7", "8", "9", "10", "12", "13", "14", "16", "18", "19", "21", "22", "23", "24"};
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : optimization test 1") {
    string filename = source_optimization;
    string queryStr = "assign a; variable v; assign n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;\
        Select BOOLEAN such that Follows* (n1, n2) and Follows* (n3, n4) and Follows* (n5, n6) and Follows* (n7, n8) and Follows* (n9, n10) pattern a(v, _)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "TRUE" };
}

//TEST_CASE("Overall test : source-sample1.txt 3")
//{
//    string filename = source_sample1;
//    string queryStr = "stmt s; Select s such that Uses(s, \"x\")";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "4", "5", "6", "7", "8", "9", "10", "12", "13", "14", "16", "18", "19", "21", "22", "23", "24" };
//    REQUIRE(result == expectedResult);
//}
//
TEST_CASE("Affects test : 1")
{
    string filename = source_affects;
    string queryStr = "stmt s; Select BOOLEAN such that Affects* (4, 14)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "TRUE" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : optimization test 2") {
    string filename = source_optimization;
    string queryStr = "assign a; variable v; assign n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;\
        Select BOOLEAN such that Next*(n1, n2) and Next*(n3, n4) and Next*(n5, n6) and Next*(n7, n8) and Next* (n9, n10) pattern a(v, _)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "TRUE" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : optimization test 3") {
    string filename = source_optimization;
    string queryStr = "assign a; variable v; assign n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;\
        Select BOOLEAN such that Next*(n1, n2) and Next*(n1, n2) and Follows*(n1, n2) and Parent(n1, n1) and Next* (n9, n10) pattern a(v, _) with n1.stmt#=n2.stmt#";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "FALSE" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : with test 1") {
    string filename = source_with;
    string queryStr = "stmt s; constant c; Select s with s.stmt# = c.value";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "4" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : invalid syntax 1") {
    string filename = source_invalid1;
    string queryStr = "stmt s; variable v; constant const; procedure p; Select p.stmt#";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "SemanticError" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : invalid syntax 2") {
    string filename = source_invalid1;
    string queryStr = "assign a;procedure p;Select <p.stmt#> ";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "SemanticError" };
    REQUIRE(result == expectedResult);
}
//
//TEST_CASE("Overall test : optimization test 4") {
//    string filename = source_optimization;
//    string queryStr = "assign a; variable v; assign n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;\
//        Select BOOLEAN such that Affects*(n1, _)";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "FALSE" };
//    REQUIRE(result == expectedResult);
//}

//TEST_CASE("Overall test :g8-7") {
//    string filename = source_g8;
//    string queryStr = "stmt s, s1; assign a, a1; print pr; read r; call c, c1; constant const; while w; if ifs; variable v; Select s such that Follows(s,_) pattern a(_, \"x\")";
//
//    set<string> result = testDriver(filename, queryStr);
//    set<string> expectedResult = { "SemanticError" };
//    REQUIRE(result == expectedResult);
//}
//
TEST_CASE("Overall test :g8-57") {
    string filename = source_g8;
    string queryStr = "stmt s, s1; assign a, a1; print pr; read r; call c, c1; constant const; while w; if ifs; variable v; procedure p;  Select v such that Parent* (s, _) such that Modifies(c, v) and Uses(a, v)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "x" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : invalid syntax 3") {
    string filename = source_invalid1;
    string queryStr = "procedure pr1, pr2; print p; read r;\
        Select pr2 such that Calls(pr1, pr2) with pr2.procName = p.varName with p1.varName = r.varName ";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "SemanticError" };
    REQUIRE(result == expectedResult);
}


TEST_CASE("Overall test : invalid syntax 4") {
    string filename = source_12;
    string queryStr = "stmt s, s1; assign a, a1; print pr; read r; call c, c1; constant const; while w; if ifs; variable v; procedure p; \
        Select v such that Modifies(c, v) and Uses(a,v) such that Parent*(s,_)";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "a,cat,x,y,z" };
    REQUIRE(result == expectedResult);
}

TEST_CASE("Overall test : invalid syntax 5") {
    string filename = source_12;
    string queryStr = "stmt s, s1; assign a, a1; print pr; read r; call c, c1; constant const; while w; if ifs; variable v; procedure p; \
        Select v such that Parent*(s,_) such that Modifies(c, v) and Uses(a,v) ";

    set<string> result = testDriver(filename, queryStr);
    set<string> expectedResult = { "a,cat,x,y,z" };
    REQUIRE(result == expectedResult);
}