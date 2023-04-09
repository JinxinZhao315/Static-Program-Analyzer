#include "catch.hpp"
#include "Constants.hpp"
#include "sp/include/extractor/Extractor.h"

ProcedureExtractor nextTestProcExtractor;

TEST_CASE("Empty Program") {
    const vector<Line>& lines = {};
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();
    unordered_map<int, set<int>> expected = {};
    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("IfElseNoLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(2, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2, 3}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("IfElseWithLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(1, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(2, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(4, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(5, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 4}},
            {3, {5}},
            {4, {5}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_whileNoLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(1, {"while", "(", "y", "==", "1", ")", "{"}, WHILE),
            Line(2, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {1}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_whileWithLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(1, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(2, {"while", "(", "y", "==", "1", ")", "{"}, WHILE),
            Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(4, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 4}},
            {3, {2}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_whileNestedInWhile") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(1, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(2, {"while", "(", "y", "==", "1", ")", "{"}, WHILE),
            Line(3, {"while", "(", "y", "==", "1", ")", "{"}, WHILE),
            Line(4, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(5, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(6, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 6}},
            {3, {4, 5}},
            {4, {3}},
            {5, {2}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_ifElseNestedInWhile") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(1, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(2, {"while", "(", "y", "==", "1", ")", "{"}, WHILE),
            Line(3, {"if", "(", "y", "==", "1", ")", "{"}, IF),
            Line(4, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(5, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(6, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(7, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 7}},
            {3, {4, 5}},
            {4, {6}},
            {5, {6}},
            {6, {2}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}


TEST_CASE("extractNextRelationship_ifElseWhileNestedInEachBranch") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}", "else", "{"}, ELSE),
            Line(4, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(5, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2, 4}},
            {2, {3}},
            {3, {2}},
            {4, {5}},
            {5, {4}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_ifElseWhileNestedInEachBranch2") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(4, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(5, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(6, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(7, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line(8, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2, 5}},
            {2, {3, 4}},
            {3, {2}},
            {4, {8}},
            {5, {6}},
            {6, {7, 8}},
            {7, {6}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_whileWithNestedIfElse") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(1, {"while", "(", "y", "==", "1", ")", "{"}, WHILE),
            Line(2, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(3, {"if", "(", "y", "==", "1", ")", "{"}, IF),
            Line(4, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(5, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(6, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(7, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2, 7}},
            {2, {3}},
            {3, {4, 5}},
            {4, {6}},
            {5, {6}},
            {6, {1}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("extractNextRelationship_ifElseEachBranchHasNestedWhileWithNestedIfElse") {
    const vector<Line> &lines = {
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(3, {"if", "(", "y", "==", "1", ")", "{"}, IF),
            Line(4, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(5, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"}", "else", "{"}, ELSE),
            Line(6, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(7, {"if", "(", "y", "==", "1", ")", "{"}, IF),
            Line(8, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(9, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2, 6}},
            {2, {3}},
            {3, {4, 5}},
            {4, {2}},
            {5, {2}},
            {6, {7}},
            {7, {8, 9}},
            {8, {6}},
            {9, {6}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("ifWithNestedIfElseInThenAndNestedWhileInElse") {
    const vector<Line>& lines = {
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(2, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(3, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(4, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}", "else", "{"}, ELSE),
            Line(5, {"while", "(", "y", "==", "1", ")", "{"}, WHILE),
            Line(6, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2, 5}},
            {2, {3, 4}},
            {5, {6}},
            {6, {5}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimple") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"y", "=", "1", ";"}, ASSIGN),
            Line(3, {"y", "=", "2", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(4, {"x", "=", "0", ";"}, ASSIGN),
            Line(5, {"x", "=", "1", ";"}, ASSIGN),
            Line(6, {"x", "=", "2", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(7, {"z", "=", "0", ";"}, ASSIGN),
            Line(8, {"z", "=", "1", ";"}, ASSIGN),
            Line(9, {"z", "=", "2", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {4, {5}},
            {5, {6}},
            {7, {8}},
            {8, {9}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProc") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(2, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(3, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(4, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(5, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(6, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(7, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(8, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(9, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2,3}},
            {4, {5,6}},
            {7, {8,9}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProcLineBeforeAndAfterIf") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "y", "+", "1", ";"}, ASSIGN),
            Line(2, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(3, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(4, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(5, {"y", "=", "y", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(6, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(7, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(8, {"x", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(9, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(10, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(11, {"z", "=", "z", "+", "1", ";"}, ASSIGN),
            Line(12, {"if", "(", "z", "==", "1", ")", "then", "{"}, IF),
            Line(13, {"z", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(14, {"z", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(15, {"z", "=", "z", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3,4}},
            {3, {5}},
            {4, {5}},
            {6, {7}},
            {7, {8,9}},
            {8, {10}},
            {9, {10}},
            {11, {12}},
            {12, {13,14}},
            {13, {15}},
            {14, {15}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProcMultipleLinesBeforeAfterAndInIf") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "y", "+", "1", ";"}, ASSIGN),
            Line(2, {"y", "=", "y", "+", "2", ";"}, ASSIGN),
            Line(3, {"y", "=", "y", "+", "3", ";"}, ASSIGN),
            Line(4, {"if", "(", "y", "==", "6", ")", "then", "{"}, IF),
            Line(5, {"y", "=", "0", ";"}, ASSIGN),
            Line(6, {"y", "=", "y", "+", "2", ";"}, ASSIGN),
            Line(7, {"y", "=", "y", "+", "3", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(8, {"y", "=", "1", ";"}, ASSIGN),
            Line(9, {"y", "=", "y", "+", "2", ";"}, ASSIGN),
            Line(10, {"y", "=", "y", "+", "3", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(11, {"y", "=", "y", "+", "1", ";"}, ASSIGN),
            Line(12, {"y", "=", "y", "+", "2", ";"}, ASSIGN),
            Line(13, {"y", "=", "y", "+", "3", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(14, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(15, {"x", "=", "x", "+", "2", ";"}, ASSIGN),
            Line(16, {"x", "=", "x", "+", "3", ";"}, ASSIGN),
            Line(17, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(18, {"x", "=", "0", ";"}, ASSIGN),
            Line(19, {"x", "=", "x", "+", "2", ";"}, ASSIGN),
            Line(20, {"x", "=", "x", "+", "3", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(21, {"x", "=", "1", ";"}, ASSIGN),
            Line(22, {"x", "=", "x", "+", "2", ";"}, ASSIGN),
            Line(23, {"x", "=", "x", "+", "3", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(24, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(25, {"x", "=", "x", "+", "2", ";"}, ASSIGN),
            Line(26, {"x", "=", "x", "+", "3", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4}},
            {4, {5,8}},
            {5, {6}},
            {6, {7}},
            {7, {11}},
            {8, {9}},
            {9, {10}},
            {10, {11}},
            {11, {12}},
            {12, {13}},
            {14, {15}},
            {15, {16}},
            {16, {17}},
            {17, {18, 21}},
            {18, {19}},
            {19, {20}},
            {20, {24}},
            {21, {22}},
            {22, {23}},
            {23, {24}},
            {24, {25}},
            {25, {26}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProc") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(2, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(3, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(4, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(5, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(6, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {1}},
            {3, {4}},
            {4, {3}},
            {5, {6}},
            {6, {5}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProcLinesBeforeAndAfterWhile") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(4, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(5, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(6, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(7, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(8, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(9, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(10, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(11, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(12, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3,4}},
            {3, {2}},
            {5, {6}},
            {6, {7,8}},
            {7, {6}},
            {9, {10}},
            {10, {11,12}},
            {11, {10}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProcMultipleLinesBeforeAfterAndInWhile") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(2, {"x", "=", "x", "+", "2", ";"}, ASSIGN),
            Line(3, {"x", "=", "x", "+", "3", ";"}, ASSIGN),
            Line(4, {"while", "(", "x", "==", "6", ")", "then", "{"}, WHILE),
            Line(5, {"x", "=", "x", "+", "4", ";"}, ASSIGN),
            Line(6, {"x", "=", "x", "+", "5", ";"}, ASSIGN),
            Line(7, {"x", "=", "x", "+", "6", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(8, {"x", "=", "x", "+", "7", ";"}, ASSIGN),
            Line(9, {"x", "=", "x", "+", "8", ";"}, ASSIGN),
            Line(10, {"x", "=", "x", "+", "9", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(11, {"y", "=", "y", "+", "1", ";"}, ASSIGN),
            Line(12, {"y", "=", "y", "+", "2", ";"}, ASSIGN),
            Line(13, {"y", "=", "y", "+", "3", ";"}, ASSIGN),
            Line(14, {"while", "(", "y", "==", "6", ")", "then", "{"}, WHILE),
            Line(15, {"y", "=", "y", "+", "4", ";"}, ASSIGN),
            Line(16, {"y", "=", "y", "+", "5", ";"}, ASSIGN),
            Line(17, {"y", "=", "y", "+", "6", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(18, {"y", "=", "y", "+", "7", ";"}, ASSIGN),
            Line(19, {"y", "=", "y", "+", "8", ";"}, ASSIGN),
            Line(20, {"y", "=", "y", "+", "9", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4}},
            {4, {5,8}},
            {5, {6}},
            {6, {7}},
            {7, {4}},
            {8, {9}},
            {9, {10}},
            {11, {12}},
            {12, {13}},
            {13, {14}},
            {14, {15,18}},
            {15, {16}},
            {16, {17}},
            {17, {14}},
            {18, {19}},
            {19, {20}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProcIfElseNestedInEachWhile") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(2, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(3, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(4, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(5, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(6, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(7, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(8, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3,4}},
            {3, {1}},
            {4, {1}},
            {5, {6}},
            {6, {7,8}},
            {7, {5}},
            {8, {5}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProcIfElseNestedInEachWhileLineBeforeAfterAndIn") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(3, {"y", "=", "0", ";"}, ASSIGN),
            Line(4, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(5, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(6, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(7, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(8, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(9, {"y", "=", "0", ";"}, ASSIGN),
            Line(10, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(11, {"y", "=", "0", ";"}, ASSIGN),
            Line(12, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(13, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(14, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(15, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(16, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3, 8}},
            {3, {4}},
            {4, {5,6}},
            {5, {7}},
            {6, {7}},
            {7, {2}},
            {9, {10}},
            {10, {11, 16}},
            {11, {12}},
            {12, {13, 14}},
            {13, {15}},
            {14, {15}},
            {15, {10}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureWithWhileInEachProcIfElseNestedInEachWhileMultipleLinesBeforeAfterAndIn") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"y", "=", "0", ";"}, ASSIGN),
            Line(3, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(4, {"y", "=", "0", ";"}, ASSIGN),
            Line(5, {"y", "=", "0", ";"}, ASSIGN),
            Line(6, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(7, {"y", "=", "0", ";"}, ASSIGN),
            Line(8, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(9, {"y", "=", "1", ";"}, ASSIGN),
            Line(10, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(11, {"y", "=", "0", ";"}, ASSIGN),
            Line(12, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(13, {"y", "=", "0", ";"}, ASSIGN),
            Line(14, {"y", "=", "0", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(15, {"x", "=", "0", ";"}, ASSIGN),
            Line(16, {"x", "=", "0", ";"}, ASSIGN),
            Line(17, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(18, {"x", "=", "0", ";"}, ASSIGN),
            Line(19, {"x", "=", "0", ";"}, ASSIGN),
            Line(20, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(21, {"x", "=", "0", ";"}, ASSIGN),
            Line(22, {"x", "=", "0", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(23, {"x", "=", "0", ";"}, ASSIGN),
            Line(24, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(25, {"x", "=", "0", ";"}, ASSIGN),
            Line(26, {"x", "=", "0", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(27, {"x", "=", "0", ";"}, ASSIGN),
            Line(28, {"x", "=", "0", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4, 13}},
            {4, {5}},
            {5, {6}},
            {6, {7, 9}},
            {7, {8}},
            {8, {11}},
            {9, {10}},
            {10, {11}},
            {11, {12}},
            {12, {3}},
            {13, {14}},
            {15, {16}},
            {16, {17}},
            {17, {18, 27}},
            {18, {19}},
            {19, {20}},
            {20, {21, 23}},
            {21, {22}},
            {22, {25}},
            {23, {24}},
            {24, {25}},
            {25, {26}},
            {26, {17}},
            {27, {28}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProcWhileInEachIf") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}", "else", "{"}, ELSE),
            Line(4, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(5, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(6, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(7, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(8, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}", "else", "{"}, ELSE),
            Line(9, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(10, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2,4}},
            {2, {3}},
            {3, {2}},
            {4, {5}},
            {5, {4}},
            {6, {7,9}},
            {7, {8}},
            {8, {7}},
            {9, {10}},
            {10, {9}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProcWhileInEachIfLineBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(2, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(4, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(5, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(6, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(7, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(8, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(9, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(10, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(11, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(12, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(13, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(14, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(15, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(16, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(17, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(18, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(19, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(20, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(21, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(22, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3,7}},
            {3, {4}},
            {4, {5,6}},
            {5, {4}},
            {6, {11}},
            {7, {8}},
            {8, {9,10}},
            {9, {8}},
            {10, {11}},
            {12, {13}},
            {13, {14, 18}},
            {14, {15}},
            {15, {16,17}},
            {16, {15}},
            {17, {22}},
            {18, {19}},
            {19, {20,21}},
            {20, {19}},
            {21, {22}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureIfElseInEachProcWhileInEachIfMultipleLinesBeforeAndAfter") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(2, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(3, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(4, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(5, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(6, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(7, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(8, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(9, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(10, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(11, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(12, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(13, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(14, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(15, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(16, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(17, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(18, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(19, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(20, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(21, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(22, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(23, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(24, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(25, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(26, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(27, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(28, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(29, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(30, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(31, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(32, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(33, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(34, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(35, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(36, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(37, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(38, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4,11}},
            {4, {5}},
            {5, {6}},
            {6, {7,9}},
            {7, {8}},
            {8, {6}},
            {9, {10}},
            {10, {18}},
            {11, {12}},
            {12, {13}},
            {13, {14, 16}},
            {14, {15}},
            {15, {13}},
            {16, {17}},
            {17, {18}},
            {18, {19}},
            {20, {21}},
            {21, {22}},
            {22, {23, 30}},
            {23, {24}},
            {24, {25}},
            {25, {26, 28}},
            {26, {27}},
            {27, {25}},
            {28, {29}},
            {29, {37}},
            {30, {31}},
            {31, {32}},
            {32, {33, 35}},
            {33, {34}},
            {34, {32}},
            {35, {36}},
            {36, {37}},
            {37, {38}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("A calls B") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"call", "B", ";"}, CALL),
            Line({"}"}, CLOSE_CURLY),

            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(2, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {};

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("A calls B from if-else") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(2, {"call", "B", ";"}, CALL),
            Line({"}", "else", "{"}, ELSE),
            Line(3, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),

            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(4, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2, 3}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("A calls B from while") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(2, {"call", "B", ";"}, CALL),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),

            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(3, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {1}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimpleWithCallsAtProcEnds") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"y", "=", "1", ";"}, ASSIGN),
            Line(3, {"call", "B", ";"}, CALL),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(4, {"x", "=", "0", ";"}, ASSIGN),
            Line(5, {"x", "=", "1", ";"}, ASSIGN),
            Line(6, {"call", "C", ";"}, CALL),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(7, {"z", "=", "0", ";"}, ASSIGN),
            Line(8, {"z", "=", "1", ";"}, ASSIGN),
            Line(9, {"z", "=", "2", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {4, {5}},
            {5, {6}},
            {7, {8}},
            {8, {9}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimpleWithCallsAtProcMiddle") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"call", "B", ";"}, CALL),
            Line(3, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(4, {"x", "=", "0", ";"}, ASSIGN),
            Line(5, {"call", "C", ";"}, CALL),
            Line(6, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(7, {"z", "=", "0", ";"}, ASSIGN),
            Line(8, {"z", "=", "2", ";"}, ASSIGN),
            Line(9, {"z", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {4, {5}},
            {5, {6}},
            {7, {8}},
            {8, {9}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimpleWithCallsAtProcStart") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"call", "B", ";"}, CALL),
            Line(2, {"y", "=", "0", ";"}, ASSIGN),
            Line(3, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(4, {"call", "C", ";"}, CALL),
            Line(5, {"x", "=", "0", ";"}, ASSIGN),
            Line(6, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(7, {"z", "=", "0", ";"}, ASSIGN),
            Line(8, {"z", "=", "2", ";"}, ASSIGN),
            Line(9, {"z", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {4, {5}},
            {5, {6}},
            {7, {8}},
            {8, {9}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimpleWithCallCycle") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"call", "B", ";"}, CALL),
            Line(2, {"y", "=", "0", ";"}, ASSIGN),
            Line(3, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(4, {"x", "=", "0", ";"}, ASSIGN),
            Line(5, {"x", "=", "1", ";"}, ASSIGN),
            Line(6, {"call", "A", ";"}, CALL),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {4, {5}},
            {5, {6}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimpleWithCallCycleInWhileLoop") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(3, {"y", "=", "2", ";"}, ASSIGN),
            Line(4, {"call", "B", ";"}, CALL),
            Line(5, {"y", "=", "2", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(6, {"y", "=", "0", ";"}, ASSIGN),
            Line(7, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(8, {"y", "=", "2", ";"}, ASSIGN),
            Line(9, {"call", "A", ";"}, CALL),
            Line(10, {"y", "=", "2", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4}},
            {4, {5}},
            {5, {2}},
            {6, {7}},
            {7, {8}},
            {8, {9}},
            {9, {10}},
            {10, {7}}
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimpleWithIndirectCallCycle") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"call", "B", ";"}, CALL),
            Line(3, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(4, {"x", "=", "0", ";"}, ASSIGN),
            Line(5, {"call", "C", ";"}, CALL),
            Line(6, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(7, {"x", "=", "0", ";"}, ASSIGN),
            Line(8, {"call", "A", ";"}, CALL),
            Line(9, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {4, {5}},
            {5, {6}},
            {7, {8}},
            {8, {9}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimpleWithCallInWhileLoop") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"y", "=", "1", ";"}, ASSIGN),
            Line(3, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(4, {"y", "=", "2", ";"}, ASSIGN),
            Line(5, {"call", "B", ";"}, CALL),
            Line({"}"}, CLOSE_CURLY),
            Line(6, {"y", "=", "3", ";"}, ASSIGN),
            Line(7, {"y", "=", "4", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(8, {"x", "=", "0", ";"}, ASSIGN),
            Line(9, {"x", "=", "1", ";"}, ASSIGN),
            Line(10, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(11, {"x", "=", "2", ";"}, ASSIGN),
            Line(12, {"x", "=", "3", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(13, {"x", "=", "4", ";"}, ASSIGN),
            Line(14, {"x", "=", "5", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4,6}},
            {4, {5}},
            {5, {3}},
            {6, {7}},
            {8, {9}},
            {9, {10}},
            {10, {11, 13}},
            {11, {12}},
            {12, {10}},
            {13, {14}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimpleWithCycleCallInIfStatement") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"if", "(", "x", "==", "1", ")", "then", "{"}, IF),
            Line(3, {"y", "=", "1", ";"}, ASSIGN),
            Line(4, {"call", "B", ";"}, CALL),
            Line(5, {"y", "=", "1", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(6, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line(7, {"call", "C", ";"}, CALL),
            Line(8, {"x", "=", "x", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(9, {"x", "=", "0", ";"}, ASSIGN),
            Line(10, {"call", "A", ";"}, CALL),
            Line(11, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(12, {"x", "=", "0", ";"}, ASSIGN),
            Line(13, {"call", "A", ";"}, CALL),
            Line(14, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3,6}},
            {3, {4}},
            {4, {5}},
            {6, {7}},
            {7, {8}},
            {9, {10}},
            {10, {11}},
            {12, {13}},
            {13, {14}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimpleWithCallInIfStatement") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"y", "=", "1", ";"}, ASSIGN),
            Line(3, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(4, {"y", "=", "2", ";"}, ASSIGN),
            Line(5, {"call", "B", ";"}, CALL),
            Line({"}", "else", "{"}, ELSE),
            Line(6, {"call", "C", ";"}, CALL),
            Line(7, {"y", "=", "y", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(8, {"y", "=", "3", ";"}, ASSIGN),
            Line(9, {"y", "=", "4", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(10, {"x", "=", "0", ";"}, ASSIGN),
            Line(11, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(12, {"z", "=", "0", ";"}, ASSIGN),
            Line(13, {"z", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4,6}},
            {4, {5}},
            {5, {8}},
            {6, {7}},
            {7, {8}},
            {8, {9}},
            {10, {11}},
            {12, {13}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimpleWithCallInNestedWhileLoop") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"y", "=", "1", ";"}, ASSIGN),
            Line(3, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(4, {"y", "=", "2", ";"}, ASSIGN),
            Line(5, {"while", "(", "x", "==", "1", ")", "then", "{"}, WHILE),
            Line(6, {"y", "=", "3", ";"}, ASSIGN),
            Line(7, {"call", "B", ";"}, CALL),
            Line(8, {"y", "=", "3", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(9, {"y", "=", "4", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(10, {"y", "=", "5", ";"}, ASSIGN),
            Line(11, {"y", "=", "6", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(12, {"x", "=", "0", ";"}, ASSIGN),
            Line(13, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4, 10}},
            {4, {5}},
            {5, {6, 9}},
            {6, {7}},
            {7, {8}},
            {8, {5}},
            {9, {3}},
            {10, {11}},
            {12, {13}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}

TEST_CASE("multiProcedureSimpleWithCallInNestedIfStatement") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"y", "=", "0", ";"}, ASSIGN),
            Line(2, {"y", "=", "1", ";"}, ASSIGN),
            Line(3, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(4, {"y", "=", "2", ";"}, ASSIGN),
            Line(5, {"if", "(", "y", "==", "1", ")", "then", "{"}, IF),
            Line(6, {"y", "=", "2", ";"}, ASSIGN),
            Line(7, {"call", "B", ";"}, CALL),
            Line({"}", "else", "{"}, ELSE),
            Line(8, {"call", "C", ";"}, CALL),
            Line(9, {"y", "=", "y", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}", "else", "{"}, ELSE),
            Line(10, {"call", "D", ";"}, CALL),
            Line(11, {"y", "=", "y", "+", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(12, {"y", "=", "3", ";"}, ASSIGN),
            Line(13, {"y", "=", "4", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "B", "{"}, PROCEDURE),
            Line(14, {"x", "=", "0", ";"}, ASSIGN),
            Line(15, {"x", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "C", "{"}, PROCEDURE),
            Line(16, {"z", "=", "0", ";"}, ASSIGN),
            Line(17, {"call", "B", ";"}, CALL),
            Line({"}"}, CLOSE_CURLY),
            Line({"procedure", "D", "{"}, PROCEDURE),
            Line(18, {"call", "C", ";"}, CALL),
            Line(19, {"z", "=", "1", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
    };
    auto [follows, followsStar] = extractFollowsRelationship(lines);
    nextTestProcExtractor.extractCallLineNumToProcName(lines);
    auto callLineNumToProcName = nextTestProcExtractor.getCallLineNumToProcName();

    unordered_map<int, set<int>> expected = {
            {1, {2}},
            {2, {3}},
            {3, {4,10}},
            {4, {5}},
            {5, {6,8}},
            {6, {7}},
            {7, {12}},
            {8, {9}},
            {9, {12}},
            {10, {11}},
            {11, {12}},
            {12, {13}},
            {14, {15}},
            {16, {17}},
            {18, {19}},
    };

    unordered_map<int, set<int>> result = extractNextRS(lines, follows);
    compareCFG(result, expected);
}
