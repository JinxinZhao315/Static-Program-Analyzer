#include "catch.hpp"
#include "Constants.hpp"
#include "source_processor/include/extractor/ConditionalRelationshipExtractor.h"

TEST_CASE("Single If with Greater Than") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">", "25", ")", "then", "{"}, IF),
            Line(2, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {
            {"c", {Line(1, {"c", "25", ">"})}}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Single If with Less Than") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", "<", "25", ")", "then", "{"}, IF),
            Line(2, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {
            {"c", {Line(1, {"c", "25", "<"})}}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Single If with Greater Than or Equal to") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">=", "25", ")", "then", "{"}, IF),
            Line(2, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {
            {"c", {Line(1, {"c", "25", ">="})}}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Single If with Less Than or Equal to") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", "<=", "25", ")", "then", "{"}, IF),
            Line(2, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {
            {"c", {Line(1, {"c", "25", "<="})}}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Single While with Greater Than") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">", "25", ")", "then", "{"}, WHILE),
            Line(2, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {
            {"c", {Line(1, {"c", "25", ">"})}}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Single While with Less Than") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", "<", "25", ")", "then", "{"}, WHILE),
            Line(2, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {
            {"c", {Line(1, {"c", "25", "<"})}}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Single While with Greater Than or Equal to") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">=", "25", ")", "then", "{"}, WHILE),
            Line(2, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {
            {"c", {Line(1, {"c", "25", ">="})}}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Single While with Less Than or Equal to") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", "<=", "25", ")", "then", "{"}, WHILE),
            Line(2, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {
            {"c", {Line(1, {"c", "25", "<="})}}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested If with Greater Than and Less Than") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">", "25", ")", "then", "{"}, IF),
            Line(2, {"if", "(", "c", "<", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {
            {"c", {
                Line(1, {"c", "25", ">"}),
                Line(2, {"c", "50", "<"})
            }},
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested If with GTE and LTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">=", "25", ")", "then", "{"}, IF),
            Line(2, {"if", "(", "c", "<=", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {
            {"c", {
                Line(1, {"c", "25", ">="}),
                Line(2, {"c", "50", "<="})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested If with GTE and LT") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">=", "25", ")", "then", "{"}, IF),
            Line(2, {"if", "(", "c", "<", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c",{
            Line(1, {"c", "25", ">="}),
            Line(2, {"c", "50", "<"})
        }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested If with GT and LTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">", "25", ")", "then", "{"}, IF),
            Line(2, {"if", "(", "c", "<=", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c",{
            Line(1, {"c", "25", ">"}),
            Line(2, {"c", "50", "<="})
        }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested If with GT and GTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">", "25", ")", "then", "{"}, IF),
            Line(2, {"if", "(", "c", ">=", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                Line(1, {"c", "25", ">"}),
                Line(2, {"c", "50", ">="})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested If with LT and LTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", "<", "25", ")", "then", "{"}, IF),
            Line(2, {"if", "(", "c", "<=", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
            "c", {
                    Line(1, {"c", "25", "<"}),
                    Line(2, {"c", "50", "<="})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested While with Greater Than and Less Than") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">", "25", ")", "then", "{"}, WHILE),
            Line(2, {"while", "(", "c", "<", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">"}),
                    Line(2, {"c", "50", "<"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested While with GTE and LTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">=", "25", ")", "then", "{"}, WHILE),
            Line(2, {"while", "(", "c", "<=", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
            "c", {
                Line(1, {"c", "25", ">="}),
                Line(2, {"c", "50", "<="})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested While with GTE and LT") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">=", "25", ")", "then", "{"}, WHILE),
            Line(2, {"while", "(", "c", "<", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c",
        {
                Line(1, {"c", "25", ">="}),
                Line(2, {"c", "50", "<"})
        }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested While with GT and LTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">", "25", ")", "then", "{"}, WHILE),
            Line(2, {"while", "(", "c", "<=", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c",
        {
                Line(1, {"c", "25", ">"}),
                Line(2, {"c", "50", "<="})
        }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested While with GT and GTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">", "25", ")", "then", "{"}, WHILE),
            Line(2, {"while", "(", "c", ">=", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c",
        {
                Line(1, {"c", "25", ">"}),
                Line(2, {"c", "50", ">="})
        }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested While with LT and LTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", "<", "25", ")", "then", "{"}, WHILE),
            Line(2, {"while", "(", "c", "<=", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c",
        {
                Line(1, {"c", "25", "<"}),
                Line(2, {"c", "50", "<="})
        }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nested While in If with Greater Than and Less Than") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">", "25", ")", "then", "{"}, IF),
            Line(2, {"while", "(", "c", "<", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedIf = {{
            "c", {
                Line(1, {"c", "25", ">"})
            }}
    };
    const unordered_map<string, set<Line>> expectedWhile = {{
        "c", {
            Line(2, {"c", "50", "<"})
        }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Nested While in If with GTE and LTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">=", "25", ")", "then", "{"}, IF),
            Line(2, {"while", "(", "c", "<=", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedIf = {{
            "c", {
                Line(1, {"c", "25", ">="})
            }}
    };
    const unordered_map<string, set<Line>> expectedWhile = {{
        "c",{
                Line(2, {"c", "50", "<="})
        }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Nested While in If with GT and LTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">", "25", ")", "then", "{"}, IF),
            Line(2, {"while", "(", "c", "<=", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedIf = {{
        "c", {
                    Line(1, {"c", "25", ">"})
            }}
    };
    const unordered_map<string, set<Line>> expectedWhile = {{
            "c", {
                Line(2, {"c", "50", "<="})
            }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Nested While in If with GTE and LT") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">=", "25", ")", "then", "{"}, IF),
            Line(2, {"while", "(", "c", "<", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedIf = {{
        "c", {
            Line(1, {"c", "25", ">="})
        }}
    };
    const unordered_map<string, set<Line>> expectedWhile = {{
            "c", {
                Line(2, {"c", "50", "<"})
            }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Nested While in If with GT and GTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">", "25", ")", "then", "{"}, IF),
            Line(2, {"while", "(", "c", ">=", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedIf = {{
        "c", {
                    Line(1, {"c", "25", ">"})
            }}
    };
    const unordered_map<string, set<Line>> expectedWhile = {{
        "c", {
                    Line(2, {"c", "50", ">="})
            }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Nested While in If with LT and LTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", "<", "25", ")", "then", "{"}, IF),
            Line(2, {"while", "(", "c", "<=", "50", ")", "then", "{"}, WHILE),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedIf = {{
        "c", {
                    Line(1, {"c", "25", "<"})
            }}
    };
    const unordered_map<string, set<Line>> expectedWhile = {{
        "c", {
                    Line(2, {"c", "50", "<="})
            }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Nested If in While with Greater Than and Less Than") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">", "25", ")", "then", "{"}, WHILE),
            Line(2, {"if", "(", "c", "<", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedWhile = {{
        "c", {
                    Line(1, {"c", "25", ">"})
            }}
    };
    const unordered_map<string, set<Line>> expectedIf = {{
        "c", {
                    Line(2, {"c", "50", "<"})
            }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Nested If in While with GTE and LTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">=", "25", ")", "then", "{"}, WHILE),
            Line(2, {"if", "(", "c", "<=", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedWhile = {{
        "c", {
                    Line(1, {"c", "25", ">="})
            }}
    };
    const unordered_map<string, set<Line>> expectedIf = {{
        "c", {
                    Line(2, {"c", "50", "<="})
            }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Nested If in While with GT and LTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">", "25", ")", "then", "{"}, WHILE),
            Line(2, {"if", "(", "c", "<=", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedWhile = {{
        "c", {
                    Line(1, {"c", "25", ">"})
            }}
    };
    const unordered_map<string, set<Line>> expectedIf = {{
        "c", {
                    Line(2, {"c", "50", "<="})
            }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Nested If in While with GTE and LT") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">=", "25", ")", "then", "{"}, WHILE),
            Line(2, {"if", "(", "c", "<", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedWhile = {{
        "c", {
                    Line(1, {"c", "25", ">="})
            }}
    };
    const unordered_map<string, set<Line>> expectedIf = {{
        "c", {
                    Line(2, {"c", "50", "<"})
            }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Nested If in While with GT and GTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">", "25", ")", "then", "{"}, WHILE),
            Line(2, {"if", "(", "c", ">=", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedWhile = {{
        "c", {
                    Line(1, {"c", "25", ">"})
            }}
    };
    const unordered_map<string, set<Line>> expectedIf = {{
        "c", {
                    Line(2, {"c", "50", ">="})
            }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Nested If in While with LT and LTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", "<", "25", ")", "then", "{"}, WHILE),
            Line(2, {"if", "(", "c", "<=", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedWhile = {{
        "c", {
                    Line(1, {"c", "25", "<"})
            }}
    };
    const unordered_map<string, set<Line>> expectedIf = {{
        "c", {
                    Line(2, {"c", "50", "<="})
            }}
    };
    const unordered_map<string, set<Line>> actualIf = extractConditionalRS(IF, lines, variables);
    const unordered_map<string, set<Line>> actualWhile = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualIf == expectedIf);
    REQUIRE(actualWhile == expectedWhile);
}

TEST_CASE("Simple if condition, GT") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">", "25", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
            "c", {
                Line(1, {"c", "25", ">"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Simple if condition, LT") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", "<", "25", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
            "c", {
                Line(1, {"c", "25", "<"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Simple if condition, GTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", ">=", "25", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">="})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Simple if condition, LTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "c", "<=", "25", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", "<="})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Simple while condition, GT") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">", "25", ")", "then", "{"}, WHILE)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Simple while condition, LT") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", "<", "25", ")", "then", "{"}, WHILE)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", "<"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Simple while condition, GTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", ">=", "25", ")", "then", "{"}, WHILE)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">="})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Simple while condition, LTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "c", "<=", "25", ")", "then", "{"}, WHILE)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", "<="})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Conjunction with GT and LT") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "(", "c", ">", "25", ")", "&&", "(", "c", "<", "50", ")", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
            "c", {
                Line(1, {"c", "25", ">", "c", "50", "<", "&&"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Conjunction with GTE and LT") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "(", "c", ">=", "25", ")", "&&", "(", "c", "<", "50", ")", ")", "then", "{"}, WHILE)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">=", "c", "50", "<", "&&"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Conjunction with GT and LTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "(", "c", ">", "25", ")", "&&", "(", "c", "<=", "50", ")", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">", "c", "50", "<=", "&&"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Conjunction with GTE and LTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "(", "c", ">=", "25", ")", "&&", "(", "c", "<=", "50", ")", ")", "then", "{"}, WHILE)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">=", "c", "50", "<=", "&&"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Conjunction with GTE and GT") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "(", "c", ">=", "25", ")", "&&", "(", "c", ">", "50", ")", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">=", "c", "50", ">", "&&"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Conjunction with LTE and LT") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "(", "c", "<=", "25", ")", "&&", "(", "c", "<", "50", ")", ")", "then", "{"}, WHILE)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", "<=", "c", "50", "<", "&&"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Disjunction with GT and LT") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "(", "c", ">", "25", ")", "||", "(", "c", "<", "50", ")", ")", "then", "{"}, WHILE)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">", "c", "50", "<", "||"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Disjunction with GTE and LT") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "(", "c", ">=", "25", ")", "||", "(", "c", "<", "50", ")", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">=", "c", "50", "<", "||"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Disjunction with GT and LTE") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "(", "c", ">", "25", ")", "||", "(", "c", "<=", "50", ")", ")", "then", "{"}, WHILE)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">", "c", "50", "<=", "||"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Disjunction with GTE and LTE") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "(", "c", ">=", "25", ")", "||", "(", "c", "<=", "50", ")", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">=", "c", "50", "<=", "||"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Disjunction with GTE and GT") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "(", "c", ">=", "25", ")", "||", "(", "c", ">", "50", ")", ")", "then", "{"}, WHILE)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">=", "c", "50", ">", "||"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Disjunction with LTE and LT") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "(", "c", "<=", "25", ")", "||", "(", "c", "<", "50", ")", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", "<=", "c", "50", "<", "||"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Conjunction and Disjunction") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "(", "c", ">", "25", ")", "&&", "(", "c", "<", "50", ")", "||", "(", "c", "!=", "30", ")", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">", "c", "50", "<", "&&", "c", "30", "!=", "||"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Disjunction and Conjunction") {
    const vector<Line>& lines = {
            Line(1, {"while", "(", "(", "c", ">", "25", ")", "||", "(", "c", "<", "50", ")", "&&", "(", "c", "!=", "30", ")", ")", "then", "{"}, WHILE)
    };
    const set<string> variables = { "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "c", {
                    Line(1, {"c", "25", ">", "c", "50", "<", "c", "30", "!=", "&&", "||"})
            }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(WHILE, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Nesting with multiple variables") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "a", ">", "25", ")", "then", "{"}, IF),
            Line(2, {"if", "(", "c", "<", "50", ")", "then", "{"}, IF),
            Line(3, {"c", "=", "c",  "-",  "1"}, ASSIGN),
            Line({"}"}, CLOSE_CURLY),
            Line({"}"}, CLOSE_CURLY)
        };
    const set<string> variables = { "a", "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {
            {"a", {
                Line(1, {"a", "25", ">"}),
            }},
            { "c", {
                Line(2, {"c", "50", "<"})
            }}
        };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Disjunction with multiple variables") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "(", "a", ">=", "25", ")", "||", "(", "c", "<=", "50", ")", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "a", "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "a", {
            Line(1, {"a", "25", ">=", "c", "50", "<=", "||"})
        }}, {
        "c", {
            Line(1, {"a", "25", ">=", "c", "50", "<=", "||"})
        }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}

TEST_CASE("Conjunction with multiple variables") {
    const vector<Line>& lines = {
            Line(1, {"if", "(", "(", "a", ">=", "25", ")", "&&", "(", "c", "<=", "50", ")", ")", "then", "{"}, IF)
    };
    const set<string> variables = { "a", "c" };
    const unordered_map<string, set<Line>> expectedConditionals = {{
        "a", {
            Line(1, {"a", "25", ">=", "c", "50", "<=", "&&"})
        }}, {
        "c", {
            Line(1, {"a", "25", ">=", "c", "50", "<=", "&&"})
        }}
    };
    const unordered_map<string, set<Line>> actualConditionals = extractConditionalRS(IF, lines, variables);
    REQUIRE(actualConditionals == expectedConditionals);
}
