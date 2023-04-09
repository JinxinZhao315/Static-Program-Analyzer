#include "catch.hpp"
#include "sp/include/extractor/AffectsRelationshipExtractor.h"

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
    clearCache();
    bool result = extractAffectsRS(lines, 1, 2, cfg, variables, modifiesRS, usesRS, false);
    REQUIRE(result);
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
    clearCache();
    bool result = extractAffectsRS(lines, 1, 2, cfg, variables, modifiesRS, usesRS, false);
    REQUIRE(!result);
}

TEST_CASE("test affects and affects star complex") {
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

    clearCache();
    bool result1 = extractAffectsRS(lines, 2, 6, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result2 = extractAffectsRS(lines, 4, 8, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result3 = extractAffectsRS(lines, 4, 10, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result4 = extractAffectsRS(lines, 6, 6, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result5 = extractAffectsRS(lines, 1, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result6 = extractAffectsRS(lines, 1, 8, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result7 = extractAffectsRS(lines, 1, 10, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result8 = extractAffectsRS(lines, 1, 12, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result9 = extractAffectsRS(lines, 2, 10, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result10 = extractAffectsRS(lines, 9, 10, cfg, variables, modifiesRS, usesRS, false);

    clearCache();
    bool result11 = extractAffectsRS(lines, 9, 11, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result12 = extractAffectsRS(lines, 9, 12, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result13 = extractAffectsRS(lines, 2, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result14 = extractAffectsRS(lines, 9, 6, cfg, variables, modifiesRS, usesRS, false);

    clearCache();
    bool result15 = extractAffectsRS(lines, 1, 4, cfg, variables, modifiesRS, usesRS, true);
    clearCache();
    bool result16 = extractAffectsRS(lines, 1, 10, cfg, variables, modifiesRS, usesRS, true);
    clearCache();
    bool result17 = extractAffectsRS(lines, 1, 11, cfg, variables, modifiesRS, usesRS, true);
    clearCache();
    bool result18 = extractAffectsRS(lines, 1, 12, cfg, variables, modifiesRS, usesRS, true);

    REQUIRE(result1);
    REQUIRE(result2);
    REQUIRE(result3);
    REQUIRE(result4);
    REQUIRE(result5);
    REQUIRE(result6);
    REQUIRE(result7);
    REQUIRE(result8);
    REQUIRE(result9);
    REQUIRE(result10);

    REQUIRE(!result11);
    REQUIRE(!result12);
    REQUIRE(!result13);
    REQUIRE(!result14);

    REQUIRE(result15);
    REQUIRE(result16);
    REQUIRE(result17);
    REQUIRE(result18);
}

TEST_CASE("test affects star simple") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "a", ";"}, ASSIGN),
            Line(2, {"v", "=", "x", ";"}, ASSIGN),
            Line(3, {"z", "=", "v", ";"}, ASSIGN),
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

    clearCache();
    bool result1 = extractAffectsRS(lines, 1, 2, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result2 = extractAffectsRS(lines, 2, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result3 = extractAffectsRS(lines, 1, 3, cfg, variables, modifiesRS, usesRS, true);

    REQUIRE(result1);
    REQUIRE(result2);
    REQUIRE(result3);
}

TEST_CASE("test affects with while") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "a", ";"}, ASSIGN),
            Line(2, {"while", "(", "a", "!=", "0", ")", "{"}, WHILE),
            Line(3, {"v", "=", "x", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(4, {"z", "=", "v", ";"}, ASSIGN),
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

    clearCache();
    bool result1 = extractAffectsRS(lines, 1, 2, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result2 = extractAffectsRS(lines, 1, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result3 = extractAffectsRS(lines, 1, 4, cfg, variables, modifiesRS, usesRS, false);

    clearCache();
    bool result4 = extractAffectsRS(lines, 2, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result5 = extractAffectsRS(lines, 2, 4, cfg, variables, modifiesRS, usesRS, false);

    clearCache();
    bool result6 = extractAffectsRS(lines, 3, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result7 = extractAffectsRS(lines, 1, 4, cfg, variables, modifiesRS, usesRS, true);

    REQUIRE(!result1);
    REQUIRE(result2);
    REQUIRE(!result3);

    REQUIRE(!result4);
    REQUIRE(!result5);

    REQUIRE(result6);
    REQUIRE(result7);
}

TEST_CASE("test affects with if") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "a", ";"}, ASSIGN),
            Line(2, {"if", "(", "a", "!=", "0", ")", "{"}, IF),
            Line(3, {"v", "=", "x", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(4, {"z", "=", "v", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
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

    clearCache();
    bool result1 = extractAffectsRS(lines, 1, 2, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result2 = extractAffectsRS(lines, 1, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result3 = extractAffectsRS(lines, 1, 4, cfg, variables, modifiesRS, usesRS, false);

    clearCache();
    bool result4 = extractAffectsRS(lines, 2, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result5 = extractAffectsRS(lines, 2, 4, cfg, variables, modifiesRS, usesRS, false);

    clearCache();
    bool result6 = extractAffectsRS(lines, 3, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result7 = extractAffectsRS(lines, 1, 4, cfg, variables, modifiesRS, usesRS, true);

    REQUIRE(!result1);
    REQUIRE(result2);
    REQUIRE(!result3);

    REQUIRE(!result4);
    REQUIRE(!result5);

    REQUIRE(!result6);
    REQUIRE(!result7);

}

TEST_CASE("test affects with nested if") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "a", ";"}, ASSIGN),
            Line(2, {"if", "(", "a", "!=", "0", ")", "{"}, IF),
            Line(3, {"if", "(", "a", "!=", "0", ")", "{"}, IF),
            Line(4, {"v", "=", "x", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(5, {"z", "=", "v", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}", "else", "{"}, ELSE),
            Line(6, {"z", "=", "v", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
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

    clearCache();
    bool result1 = extractAffectsRS(lines, 1, 2, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result2 = extractAffectsRS(lines, 1, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result3 = extractAffectsRS(lines, 1, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result4 = extractAffectsRS(lines, 1, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result5 = extractAffectsRS(lines, 1, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result1);
    REQUIRE(!result2);
    REQUIRE(result3);
    REQUIRE(!result4);
    REQUIRE(!result5);

    clearCache();
    bool result6 = extractAffectsRS(lines, 2, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result7 = extractAffectsRS(lines, 2, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result8 = extractAffectsRS(lines, 2, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result9 = extractAffectsRS(lines, 2, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result6);
    REQUIRE(!result7);
    REQUIRE(!result8);
    REQUIRE(!result9);

    clearCache();
    bool result10 = extractAffectsRS(lines, 3, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result11 = extractAffectsRS(lines, 3, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result12 = extractAffectsRS(lines, 3, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result10);
    REQUIRE(!result11);
    REQUIRE(!result12);

    clearCache();
    bool result13 = extractAffectsRS(lines, 4, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result14 = extractAffectsRS(lines, 4, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result13);
    REQUIRE(!result14);

    clearCache();
    bool result15 = extractAffectsRS(lines, 1, 5, cfg, variables, modifiesRS, usesRS, true);
    clearCache();
    bool result16 = extractAffectsRS(lines, 1, 6, cfg, variables, modifiesRS, usesRS, true);

    REQUIRE(!result15);
    REQUIRE(!result16);
}

TEST_CASE("test affects with nested while") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "a", ";"}, ASSIGN),
            Line(2, {"while", "(", "a", "!=", "0", ")", "{"}, WHILE),
            Line(3, {"while", "(", "a", "!=", "0", ")", "{"}, WHILE),
            Line(4, {"v", "=", "x", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line(5, {"z", "=", "v", ";"}, ASSIGN),
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

    clearCache();
    bool result1 = extractAffectsRS(lines, 1, 2, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result2 = extractAffectsRS(lines, 1, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result3 = extractAffectsRS(lines, 1, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result4 = extractAffectsRS(lines, 1, 5, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result1);
    REQUIRE(!result2);
    REQUIRE(result3);
    REQUIRE(!result4);

    clearCache();
    bool result5 = extractAffectsRS(lines, 2, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result6 = extractAffectsRS(lines, 2, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result7 = extractAffectsRS(lines, 2, 5, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result5);
    REQUIRE(!result6);
    REQUIRE(!result7);

    clearCache();
    bool result8 = extractAffectsRS(lines, 3, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result9 = extractAffectsRS(lines, 3, 5, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result8);
    REQUIRE(!result9);

    clearCache();
    bool result10 = extractAffectsRS(lines, 4, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result11 = extractAffectsRS(lines, 1, 5, cfg, variables, modifiesRS, usesRS, true);
    REQUIRE(result10);
    REQUIRE(result11);
}

TEST_CASE("test affects with if nested in while") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "a", ";"}, ASSIGN),
            Line(2, {"while", "(", "a", "!=", "0", ")", "{"}, WHILE),
            Line(3, {"if", "(", "a", "!=", "0", ")", "{"}, IF),
            Line(4, {"v", "=", "x", ";"}, ASSIGN),
            Line({"}", "else", "{"}, ELSE),
            Line(5, {"v", "=", "x", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY),
            Line(6, {"z", "=", "v", ";"}, ASSIGN),
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

    clearCache();
    bool result1 = extractAffectsRS(lines, 1, 2, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result2 = extractAffectsRS(lines, 1, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result3 = extractAffectsRS(lines, 1, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result4 = extractAffectsRS(lines, 1, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result5 = extractAffectsRS(lines, 1, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result1);
    REQUIRE(!result2);
    REQUIRE(result3);
    REQUIRE(result4);
    REQUIRE(!result5);

    clearCache();
    bool result6 = extractAffectsRS(lines, 2, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result7 = extractAffectsRS(lines, 2, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result8 = extractAffectsRS(lines, 2, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result9 = extractAffectsRS(lines, 2, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result6);
    REQUIRE(!result7);
    REQUIRE(!result8);
    REQUIRE(!result9);

    clearCache();
    bool result10 = extractAffectsRS(lines, 3, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result11 = extractAffectsRS(lines, 3, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result12 = extractAffectsRS(lines, 3, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result10);
    REQUIRE(!result11);
    REQUIRE(!result12);

    clearCache();
    bool result13 = extractAffectsRS(lines, 4, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result14 = extractAffectsRS(lines, 4, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result13);
    REQUIRE(result14);

    clearCache();
    bool result15 = extractAffectsRS(lines, 5, 6, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result16 = extractAffectsRS(lines, 1, 6, cfg, variables, modifiesRS, usesRS, true);

    REQUIRE(result15);
    REQUIRE(result16);
}

TEST_CASE("test affects with while nested in if") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "a", ";"}, ASSIGN),
            Line(2, {"if", "(", "a", "!=", "0", ")", "{"}, IF),
            Line(3, {"while", "(", "a", "!=", "0", ")", "{"}, WHILE),
            Line(4, {"v", "=", "x", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}", "else", "{"}, ELSE),
            Line(5, {"v", "=", "x", ";"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line(6, {"x", "=", "v", ";"}, ASSIGN),
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

    clearCache();
    bool result1 = extractAffectsRS(lines, 1, 2, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result2 = extractAffectsRS(lines, 1, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result3 = extractAffectsRS(lines, 1, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result4 = extractAffectsRS(lines, 1, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result5 = extractAffectsRS(lines, 1, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result1);
    REQUIRE(!result2);
    REQUIRE(result3);
    REQUIRE(result4);
    REQUIRE(!result5);

    clearCache();
    bool result6 = extractAffectsRS(lines, 2, 3, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result7 = extractAffectsRS(lines, 2, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result8 = extractAffectsRS(lines, 2, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result9 = extractAffectsRS(lines, 2, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result6);
    REQUIRE(!result7);
    REQUIRE(!result8);
    REQUIRE(!result9);

    clearCache();
    bool result10 = extractAffectsRS(lines, 3, 4, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result11 = extractAffectsRS(lines, 3, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result12 = extractAffectsRS(lines, 3, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result10);
    REQUIRE(!result11);
    REQUIRE(!result12);

    clearCache();
    bool result13 = extractAffectsRS(lines, 4, 5, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result14 = extractAffectsRS(lines, 4, 6, cfg, variables, modifiesRS, usesRS, false);

    REQUIRE(!result13);
    REQUIRE(result14);

    clearCache();
    bool result15 = extractAffectsRS(lines, 5, 6, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    bool result16 = extractAffectsRS(lines, 1, 6, cfg, variables, modifiesRS, usesRS, true);

    REQUIRE(result15);
    REQUIRE(result16);
}

TEST_CASE("test affects with wildcards simple") {
    const vector<Line>& lines = {
            Line({"procedure", "A", "{"}, PROCEDURE),
            Line(1, {"x", "=", "a", ";"}, ASSIGN),
            Line(2, {"v", "=", "x", ";"}, ASSIGN),
            Line(3, {"z", "=", "v", ";"}, ASSIGN),
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

    clearCache();
    set<int> result1 = extractAffectsWithWildcard(lines, 1, false, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    set<int> result2 = extractAffectsWithWildcard(lines, 1, true, cfg, variables, modifiesRS, usesRS, false);

    set<int> expected1 = { 2 };
    set<int> expected2 = {  };

    REQUIRE(result1 == expected1);
    REQUIRE(result2 == expected2);

    clearCache();
    set<int> result3 = extractAffectsWithWildcard(lines, 2, false, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    set<int> result4 = extractAffectsWithWildcard(lines, 2, true, cfg, variables, modifiesRS, usesRS, false);

    set<int> expected3 = { 3 };
    set<int> expected4 = { 1 };

    REQUIRE(result3 == expected3);
    REQUIRE(result4 == expected4);

    clearCache();
    set<int> result5 = extractAffectsWithWildcard(lines, 3, false, cfg, variables, modifiesRS, usesRS, false);
    clearCache();
    set<int> result6 = extractAffectsWithWildcard(lines, 3, true, cfg, variables, modifiesRS, usesRS, false);

    set<int> expected5 = { };
    set<int> expected6 = { 2 };

    REQUIRE(result5 == expected5);
    REQUIRE(result6 == expected6);

    unordered_map<int, set<int>> result7 = extractAffectsWithMultipleWildcards(lines, cfg, variables, modifiesRS, usesRS, false);
    unordered_map<int, set<int>> expected7 = {
            {1, {2}},
            {2, {3}},
    };

    REQUIRE(result7 == expected7);

    clearCache();
    set<int> result8 = extractAffectsWithWildcard(lines, 1, false, cfg, variables, modifiesRS, usesRS, true);
    clearCache();
    set<int> result9 = extractAffectsWithWildcard(lines, 1, true, cfg, variables, modifiesRS, usesRS, true);

    set<int> expected8 = { 2, 3 };
    set<int> expected9 = {  };

    REQUIRE(result8 == expected8);
    REQUIRE(result9 == expected9);

    clearCache();
    set<int> result10 = extractAffectsWithWildcard(lines, 2, false, cfg, variables, modifiesRS, usesRS, true);
    clearCache();
    set<int> result11 = extractAffectsWithWildcard(lines, 2, true, cfg, variables, modifiesRS, usesRS, true);

    set<int> expected10 = { 3 };
    set<int> expected11 = { 1 };

    REQUIRE(result10 == expected10);
    REQUIRE(result11 == expected11);

    clearCache();
    set<int> result12 = extractAffectsWithWildcard(lines, 3, false, cfg, variables, modifiesRS, usesRS, true);
    clearCache();
    set<int> result13 = extractAffectsWithWildcard(lines, 3, true, cfg, variables, modifiesRS, usesRS, true);

    set<int> expected12 = { };
    set<int> expected13 = { 1, 2 };

    REQUIRE(result12 == expected12);
    REQUIRE(result13 == expected13);

    unordered_map<int, set<int>> result14 = extractAffectsWithMultipleWildcards(lines, cfg, variables, modifiesRS, usesRS, true);
    unordered_map<int, set<int>> expected14 = {
            {1, {2, 3}},
            {2, {3}},
    };

    REQUIRE(result14 == expected14);
}
