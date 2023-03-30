#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/Extractor.h"
#include "source_processor/include/extractor/AffectsRelationshipExtractor.h"
//
//ProcedureExtractor affectsTestProcExtractor;
//
//TEST_CASE("Affects: A calls B") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"call", "B", ";"}, CALL),
//        Line({"}"}, CLOSE_CURLY),
//
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(2, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2}},
//        {2, {1}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: A calls B from if-else") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
//        Line(2, {"call", "B", ";"}, CALL),
//        Line({"}", "else", "{"}, ELSE),
//        Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"}"}, CLOSE_CURLY),
//
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(4, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2, 3}},
//        {2, {4}},
//        {4, {2}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: A calls B from while") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
//        Line(2, {"call", "B", ";"}, CALL),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"}"}, CLOSE_CURLY),
//
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(3, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2}},
//        {2, {1, 3}},
//        {3, {2}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: multiProcedureSimpleWithCallsAtProcEnds") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"y", "=", "0", ";"}, ASSIGN),
//        Line(2, {"y", "=", "1", ";"}, ASSIGN),
//        Line(3, {"call", "B", ";"}, CALL),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(4, {"x", "=", "0", ";"}, ASSIGN),
//        Line(5, {"x", "=", "1", ";"}, ASSIGN),
//        Line(6, {"call", "C", ";"}, CALL),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "C", "{"}, PROCEDURE),
//        Line(7, {"z", "=", "0", ";"}, ASSIGN),
//        Line(8, {"z", "=", "1", ";"}, ASSIGN),
//        Line(9, {"z", "=", "2", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2}},
//        {2, {3}},
//        {3, {4}},
//        {4, {5}},
//        {5, {6}},
//        {6, {3, 7}},
//        {7, {8}},
//        {8, {9}},
//        {9, {6}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: multiProcedureSimpleWithCallsAtProcMiddle") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"y", "=", "0", ";"}, ASSIGN),
//        Line(2, {"call", "B", ";"}, CALL),
//        Line(3, {"y", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(4, {"x", "=", "0", ";"}, ASSIGN),
//        Line(5, {"call", "C", ";"}, CALL),
//        Line(6, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "C", "{"}, PROCEDURE),
//        Line(7, {"z", "=", "0", ";"}, ASSIGN),
//        Line(8, {"z", "=", "2", ";"}, ASSIGN),
//        Line(9, {"z", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2}},
//        {2, {3, 4}},
//        {4, {5}},
//        {5, {6, 7}},
//        {6, {2}},
//        {7, {8}},
//        {8, {9}},
//        {9, {5}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: multiProcedureSimpleWithCallsAtProcStart") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"call", "B", ";"}, CALL),
//        Line(2, {"y", "=", "0", ";"}, ASSIGN),
//        Line(3, {"y", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(4, {"call", "C", ";"}, CALL),
//        Line(5, {"x", "=", "0", ";"}, ASSIGN),
//        Line(6, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "C", "{"}, PROCEDURE),
//        Line(7, {"z", "=", "0", ";"}, ASSIGN),
//        Line(8, {"z", "=", "2", ";"}, ASSIGN),
//        Line(9, {"z", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2, 4}},
//        {2, {3}},
//        {4, {5, 7}},
//        {5, {6}},
//        {6, {1}},
//        {7, {8}},
//        {8, {9}},
//        {9, {4}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: multiProcedureSimpleWithCallCycle") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"call", "B", ";"}, CALL),
//        Line(2, {"y", "=", "0", ";"}, ASSIGN),
//        Line(3, {"y", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(4, {"x", "=", "0", ";"}, ASSIGN),
//        Line(5, {"x", "=", "1", ";"}, ASSIGN),
//        Line(6, {"call", "A", ";"}, CALL),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2, 4}},
//        {2, {3}},
//        {3, {6}},
//        {4, {5}},
//        {5, {6}},
//        {6, {1}},
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: multiProcedureSimpleWithCallCycleInWhileLoop") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"y", "=", "0", ";"}, ASSIGN),
//        Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
//        Line(3, {"y", "=", "2", ";"}, ASSIGN),
//        Line(4, {"call", "B", ";"}, CALL),
//        Line(5, {"y", "=", "2", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(6, {"y", "=", "0", ";"}, ASSIGN),
//        Line(7, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
//        Line(8, {"y", "=", "2", ";"}, ASSIGN),
//        Line(9, {"call", "A", ";"}, CALL),
//        Line(10, {"y", "=", "2", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2}},
//        {2, {3, 9}},
//        {3, {4}},
//        {4, {5, 6}},
//        {5, {2}},
//        {6, {7}},
//        {7, {4, 8}},
//        {8, {9}},
//        {9, {1, 10}},
//        {10, {7}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: multiProcedureSimpleWithIndirectCallCycle") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"y", "=", "0", ";"}, ASSIGN),
//        Line(2, {"call", "B", ";"}, CALL),
//        Line(3, {"y", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(4, {"x", "=", "0", ";"}, ASSIGN),
//        Line(5, {"call", "C", ";"}, CALL),
//        Line(6, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "C", "{"}, PROCEDURE),
//        Line(7, {"x", "=", "0", ";"}, ASSIGN),
//        Line(8, {"call", "A", ";"}, CALL),
//        Line(9, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2}},
//        {2, {3, 4}},
//        {3, {8}},
//        {4, {5}},
//        {5, {6, 7}},
//        {6, {2}},
//        {7, {8}},
//        {8, {1, 9}},
//        {9, {5}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: multiProcedureSimpleWithCallInWhileLoop") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"y", "=", "0", ";"}, ASSIGN),
//        Line(2, {"y", "=", "1", ";"}, ASSIGN),
//        Line(3, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
//        Line(4, {"y", "=", "2", ";"}, ASSIGN),
//        Line(5, {"call", "B", ";"}, CALL),
//        Line({"}"}, CLOSE_CURLY),
//        Line(6, {"y", "=", "3", ";"}, ASSIGN),
//        Line(7, {"y", "=", "4", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(8, {"x", "=", "0", ";"}, ASSIGN),
//        Line(9, {"x", "=", "1", ";"}, ASSIGN),
//        Line(10, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
//        Line(11, {"x", "=", "2", ";"}, ASSIGN),
//        Line(12, {"x", "=", "3", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line(13, {"x", "=", "4", ";"}, ASSIGN),
//        Line(14, {"x", "=", "5", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2}},
//        {2, {3}},
//        {3, {4,6}},
//        {4, {5}},
//        {5, {3,8}},
//        {6, {7}},
//        {8, {9}},
//        {9, {10}},
//        {10, {11, 13}},
//        {11, {12}},
//        {12, {10}},
//        {13, {14}},
//        {14, {5}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: multiProcedureSimpleWithCycleCallInIfStatement") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"y", "=", "0", ";"}, ASSIGN),
//        Line(2, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
//        Line(3, {"y", "=", "1", ";"}, ASSIGN),
//        Line(4, {"call", "B", ";"}, CALL),
//        Line(5, {"y", "=", "1", ";"}, ASSIGN),
//        Line({"}", "else", "{"}, ELSE),
//        Line(6, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
//        Line(7, {"call", "C", ";"}, CALL),
//        Line(8, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(9, {"x", "=", "0", ";"}, ASSIGN),
//        Line(10, {"call", "A", ";"}, CALL),
//        Line(11, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "C", "{"}, PROCEDURE),
//        Line(12, {"x", "=", "0", ";"}, ASSIGN),
//        Line(13, {"call", "A", ";"}, CALL),
//        Line(14, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2}},
//        {2, {3,6}},
//        {3, {4}},
//        {4, {5,9}},
//        {5, {10, 13}},
//        {6, {7}},
//        {7, {8,12}},
//        {8, {10, 13}},
//        {9, {10}},
//        {10, {1, 11}},
//        {11, {4}},
//        {12, {13}},
//        {13, {1, 14}},
//        {14, {7}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: multiProcedureSimpleWithCallInIfStatement") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"y", "=", "0", ";"}, ASSIGN),
//        Line(2, {"y", "=", "1", ";"}, ASSIGN),
//        Line(3, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
//        Line(4, {"y", "=", "2", ";"}, ASSIGN),
//        Line(5, {"call", "B", ";"}, CALL),
//        Line({"}", "else", "{"}, ELSE),
//        Line(6, {"call", "C", ";"}, CALL),
//        Line(7, {"y", "=", "y", "+", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line(8, {"y", "=", "3", ";"}, ASSIGN),
//        Line(9, {"y", "=", "4", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(10, {"x", "=", "0", ";"}, ASSIGN),
//        Line(11, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "C", "{"}, PROCEDURE),
//        Line(12, {"z", "=", "0", ";"}, ASSIGN),
//        Line(13, {"z", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2}},
//        {2, {3}},
//        {3, {4,6}},
//        {4, {5}},
//        {5, {8,10}},
//        {6, {7,12}},
//        {7, {8}},
//        {8, {9}},
//        {10, {11}},
//        {11, {5}},
//        {12, {13}},
//        {13, {6}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: multiProcedureSimpleWithCallInNestedWhileLoop") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"y", "=", "0", ";"}, ASSIGN),
//        Line(2, {"y", "=", "1", ";"}, ASSIGN),
//        Line(3, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
//        Line(4, {"y", "=", "2", ";"}, ASSIGN),
//        Line(5, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
//        Line(6, {"y", "=", "3", ";"}, ASSIGN),
//        Line(7, {"call", "B", ";"}, CALL),
//        Line(8, {"y", "=", "3", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line(9, {"y", "=", "4", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line(10, {"y", "=", "5", ";"}, ASSIGN),
//        Line(11, {"y", "=", "6", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(12, {"x", "=", "0", ";"}, ASSIGN),
//        Line(13, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2}},
//        {2, {3}},
//        {3, {4, 10}},
//        {4, {5}},
//        {5, {6, 9}},
//        {6, {7}},
//        {7, {8, 12}},
//        {8, {5}},
//        {9, {3}},
//        {10, {11}},
//        {12, {13}},
//        {13, {7}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}
//
//TEST_CASE("Affects: multiProcedureSimpleWithCallInNestedIfStatement") {
//const vector<Line>& lines = {
//        Line({"procedure", "A", "{"}, PROCEDURE),
//        Line(1, {"y", "=", "0", ";"}, ASSIGN),
//        Line(2, {"y", "=", "1", ";"}, ASSIGN),
//        Line(3, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
//        Line(4, {"y", "=", "2", ";"}, ASSIGN),
//        Line(5, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
//        Line(6, {"y", "=", "2", ";"}, ASSIGN),
//        Line(7, {"call", "B", ";"}, CALL),
//        Line({"}", "else", "{"}, ELSE),
//        Line(8, {"call", "C", ";"}, CALL),
//        Line(9, {"y", "=", "y", "+", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"}", "else", "{"}, ELSE),
//        Line(10, {"call", "D", ";"}, CALL),
//        Line(11, {"y", "=", "y", "+", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line(12, {"y", "=", "3", ";"}, ASSIGN),
//        Line(13, {"y", "=", "4", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "B", "{"}, PROCEDURE),
//        Line(14, {"x", "=", "0", ";"}, ASSIGN),
//        Line(15, {"x", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "C", "{"}, PROCEDURE),
//        Line(16, {"z", "=", "0", ";"}, ASSIGN),
//        Line(17, {"call", "B", ";"}, CALL),
//        Line({"}"}, CLOSE_CURLY),
//        Line({"procedure", "D", "{"}, PROCEDURE),
//        Line(18, {"call", "C", ";"}, CALL),
//        Line(19, {"z", "=", "1", ";"}, ASSIGN),
//        Line({"}"}, CLOSE_CURLY),
//};
//auto [follows, followsStar] = extractFollowsRelationship(lines);
//affectsTestProcExtractor.extractCallLineNumToProcName(lines);
//auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
//
//unordered_map<int, set<int>> expected = {
//        {1, {2}},
//        {2, {3}},
//        {3, {4,10}},
//        {4, {5}},
//        {5, {6,8}},
//        {6, {7}},
//        {7, {12,14}},
//        {8, {9, 16}},
//        {9, {12}},
//        {10, {11,18}},
//        {11, {12}},
//        {12, {13}},
//        {14, {15}},
//        {15, {7, 17}},
//        {16, {17}},
//        {17, {8, 14, 18}},
//        {18, {16,19}},
//        {19, {10}}
//};
//
//unordered_map<int, set<int>> result = extractNextRS(lines, follows, callLineNumToProcName, false);
//compareCFG(result, expected);
//}

void printPaths(vector<vector<int>> paths) {
    for(auto path: paths) {
        for (auto node: path) {
            cout << node << " ";
        }
        cout << endl;
    }
}

TEST_CASE("test affects simple") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"x", "=", "y", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    ProcedureExtractor affectsTestProcExtractor;
    VariableExtractor variableExtractor;
    variableExtractor.extractVariables(lines);
    set<string> variables = variableExtractor.getVariables();
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    affectsTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
    unordered_map<int, set<int>> cfg = extractNextRS(lines, follows);
    auto modifiesUses = extractModifiesUsesAndCallRS(lines, variables);
    auto modifiesRS = modifiesUses.modifiesRS;
    auto usesRS = modifiesUses.usesRS;
    set<string> result = extractAffectsRS(lines, 1, 2, cfg, variables, modifiesRS, usesRS);
    set<string> expected = {"y"};
    REQUIRE(expected == result);
}

TEST_CASE("test affects with calls") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"call", "B", ";"}, CALL),
            Line(3, {"x", "=", "y", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(4, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    ProcedureExtractor affectsTestProcExtractor;
    VariableExtractor variableExtractor;
    variableExtractor.extractVariables(lines);
    set<string> variables = variableExtractor.getVariables();
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    affectsTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
    unordered_map<int, set<int>> cfg = extractNextRS(lines, follows);
    auto modifiesUses = extractModifiesUsesAndCallRS(lines, variables);
    auto modifiesRS = modifiesUses.modifiesRS;
    auto usesRS = modifiesUses.usesRS;
    set<string> result = extractAffectsRS(lines, 1, 2, cfg, variables, modifiesRS, usesRS);
    set<string> expected = {};
    REQUIRE(expected == result);
}

TEST_CASE("test affects complex") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "0", ";"}, ASSIGN),
            Line(2, {"i", "=", "5", ";"}, ASSIGN),
            Line(3, {"while", "(", "i", "!=", "0", ")", "{"}, WHILE),
            Line(4, {"x", "=", "x", "+", "2", "*", "y"}, ASSIGN),
            Line(5, {"call", "B", ";"}, CALL),
            Line(6, {"i", "=", "i", "-", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(7, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(8, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(9, {"z", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(10, {"z", "=", "z", "+", "x", "+", "i", ";"}, ASSIGN),
            Line(11, {"y", "=", "z", "+", "2"}, ASSIGN),
            Line(12, {"x", "=", "x", "*", "y", "+", "z", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY)
    };
    ProcedureExtractor affectsTestProcExtractor;
    VariableExtractor variableExtractor;
    variableExtractor.extractVariables(lines);
    set<string> variables = variableExtractor.getVariables();
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    affectsTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = affectsTestProcExtractor.getCallLineNumToProcName();
    unordered_map<int, set<int>> cfg = extractNextRS(lines, follows);
    auto modifiesUses = extractModifiesUsesAndCallRS(lines, variables);
    auto modifiesRS = modifiesUses.modifiesRS;
    auto usesRS = modifiesUses.usesRS;

    set<string> result1 = extractAffectsRS(lines, 2, 6, cfg, variables, modifiesRS, usesRS);
    set<string> expected1 = { "i" };
    set<string> result2 = extractAffectsRS(lines, 4, 8, cfg, variables, modifiesRS, usesRS);
    set<string> expected2 = { "x" };
    set<string> result3 = extractAffectsRS(lines, 4, 10, cfg, variables, modifiesRS, usesRS);
    set<string> expected3 = { "x" };
    set<string> result4 = extractAffectsRS(lines, 6, 6, cfg, variables, modifiesRS, usesRS);
    set<string> expected4 = { "i" };
    set<string> result5 = extractAffectsRS(lines, 1, 4, cfg, variables, modifiesRS, usesRS);
    set<string> expected5 = { "x" };
    set<string> result6 = extractAffectsRS(lines, 1, 8, cfg, variables, modifiesRS, usesRS);
    set<string> expected6 = { "x" };
    set<string> result7 = extractAffectsRS(lines, 1, 10, cfg, variables, modifiesRS, usesRS);
    set<string> expected7 = { "x" };
    set<string> result8 = extractAffectsRS(lines, 1, 12, cfg, variables, modifiesRS, usesRS);
    set<string> expected8 = { "x" };
    set<string> result9 = extractAffectsRS(lines, 2, 10, cfg, variables, modifiesRS, usesRS);
    set<string> expected9 = { "i" };
    set<string> result10 = extractAffectsRS(lines, 9, 10, cfg, variables, modifiesRS, usesRS);
    set<string> expected10 = { "z" };

    set<string> result11 = extractAffectsRS(lines, 9, 11, cfg, variables, modifiesRS, usesRS);
    set<string> expected11 = { };
    set<string> result12 = extractAffectsRS(lines, 9, 12, cfg, variables, modifiesRS, usesRS);
    set<string> expected12 = { };
    set<string> result13 = extractAffectsRS(lines, 2, 3, cfg, variables, modifiesRS, usesRS);
    set<string> expected13 = { };
    set<string> result14 = extractAffectsRS(lines, 9, 6, cfg, variables, modifiesRS, usesRS);
    set<string> expected14 = { };

    REQUIRE(result1 == expected1);
    REQUIRE(result2 == expected2);
    REQUIRE(result3 == expected3);
    REQUIRE(result4 == expected4);
    REQUIRE(result5 == expected5);
    REQUIRE(result6 == expected6);
    REQUIRE(result7 == expected7);
    REQUIRE(result8 == expected8);
    REQUIRE(result9 == expected9);
    REQUIRE(result10 == expected10);

    REQUIRE(result11 == expected11);
    REQUIRE(result12 == expected12);
    REQUIRE(result13 == expected13);
    REQUIRE(result14 == expected14);
}
