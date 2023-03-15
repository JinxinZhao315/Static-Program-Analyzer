#include "Constants.hpp"

const vector<Line> mainProgram = {
        Line({"procedure", "main", "{"}, "procedure"),
        Line(1, {"flag", "=", "0", ";"}, "="),
        Line(2, {"call", "computeCentroid", ";"}, "call"),
        Line(3, {"call", "printResults", ";"}, "call"),
        Line({"}"}, "}"),
};

const set<string> mainProgramVariables = {"flag"};

const vector<Line> onlyCallStatements = {
        Line({"procedure", "main", "{"}, "procedure"),
        Line(2, {"call", "computeCentroid", ";"}, "call"),
        Line(3, {"call", "printResults", ";"}, "call"),
        Line({"}"}, "}"),
};

const set<string> onlyCallStatementsVariables;

const vector<Line> singleAssignmentSelfIncrement = {
        Line(6, {"count", "=", "count", "+", "1", ";"}, "=")
};

const set<string> singleAssignmentSelfIncrementVariables = {"count"};

const vector<Line> singleAssignmentAddVariable = {
        Line(7, {"cenX", "=", "cenX", "+", "x", ";"}, "=")
};

const set<string> singleAssignmentAddVariableVariables = {"cenX", "x"};

const vector<Line> whileLoop = {
        Line(5, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, "while"),
        Line(6, {"count", "=", "count", "+", "1", ";"}, "="),
        Line(7, {"cenX", "=", "cenX", "+", "x", ";"}, "="),
        Line(8, {"cenY", "=", "cenY", "+", "y", ";"}, "="),
        Line(9, {"call", "readPoint", ";"}, "call"),
        Line({"}"}, "}"),
};

const set<string> whileLoopVariables = {"x", "y", "count", "cenX", "cenY"};

const vector<Line> whileLoop2 = {
        Line(4, {"call", "readPoint", ";"}, "call"),
        Line(5, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, "while"),
        Line(6, {"count", "=", "count", "+", "1", ";"}, "="),
        Line(7, {"cenX", "=", "cenX", "+", "x", ";"}, "="),
        Line(8, {"cenY", "=", "cenY", "+", "y", ";"}, "="),
        Line(9, {"call", "readPoint", ";"}, "call"),
        Line({"}"}, "}"),
        Line(10, {"call", "readPoint", ";"}, "call"),
};

const vector<Line> whileLoopInProcedure = {
        Line({"procedure", "whileLoopInProcedure", "{"}, "procedure"),
        Line(1, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, "while"),
        Line(2, {"count", "=", "count", "+", "1", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}")
};

const vector<Line> whileLoopInProcedureWithLinesBeforeAfter = {
        Line({"procedure", "whileLoopInProcedure", "{"}, "procedure"),
        Line(1, {"count", "=", "0", ";"}, "="),
        Line(2, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, "while"),
        Line(3, {"count", "=", "count", "+", "1", ";"}, "="),
        Line({"}"}, "}"),
        Line(4, {"call", "readPoint", ";"}, "call"),
        Line({"}"}, "}")
};

const set<string> whileLoop2Variables = {"x", "y", "count", "cenX", "cenY"};

const vector<Line> computeCentroid = {
        Line({"procedure", "computeCentroid", "{"}, "procedure"),
        Line(1, {"count", "=", "0", ";"}, "="),
        Line(2, {"cenX", "=", "0", ";"}, "="),
        Line(3, {"cenY", "=", "0", ";"}, "="),
        Line(4, {"call", "readPoint", ";"}, "call"),
        Line(5, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, "while"),
        Line(6, {"count", "=", "count", "+", "1", ";"}, "="),
        Line(7, {"cenX", "=", "cenX", "+", "x", ";"}, "="),
        Line(8, {"cenY", "=", "cenY", "+", "y", ";"}, "="),
        Line(9, {"call", "readPoint", ";"}, "call"),
        Line({"}"}, "}"),
        Line(10, {"if", "(", "count", "==", "0", ")", "{"}, "if"),
        Line(11, {"flag", "=", "1", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(12, {"cenX", "=", "cenX", "/", "count", ";"}, "="),
        Line(13, {"cenY", "=", "cenY", "/", "count", ";"}, "="),
        Line({"}"}, "}"),
        Line(14, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, "="),
        Line({"}"}, "}"),
};

const set<string> computeCentroidVariables = {"x", "y", "count", "cenX", "cenY", "flag", "normSq"};

const vector<Line> ifElse = {
        Line(19, {"if", "(", "count", "==", "0", ")", "{"}, "if"),
        Line(20, {"flag", "=", "1", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, "="),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, "="),
        Line({"}"}, "}"),
};

const vector<Line> ifElseInProcedure = {
        Line({"procedure", "ifElseInProcedure", "{"}, "procedure"),
        Line(1, {"flag", "=", "1", ";"}, "="),
        Line(2, {"if", "(", "count", "==", "0", ")", "{"}, "if"),
        Line(3, {"flag", "=", "1", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(4, {"cenX", "=", "cenX", "/", "count", ";"}, "="),
        Line({"}"}, "}"),
        Line(5, {"flag", "=", "1", ";"}, "="),
        Line({"}"}, "}"),
};

const set<string> ifElseVariables = {"count", "cenX", "cenY", "flag"};

const vector<Line> ifElse2 = {
        Line(18, {"call", "readPoint", ";"}, "call"),
        Line(19, {"if", "(", "count", "==", "0", ")", "{"}, "if"),
        Line(20, {"flag", "=", "1", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, "="),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, "="),
        Line({"}"}, "}"),
        Line(23, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, "="),
};

const set<string> ifElse2Variables = {"count", "cenX", "cenY", "flag", "normSq"};

const vector<Line> superNested = {
        Line({"procedure", "proc1", "{"}, "procedure"),
        Line(1, {"a", "=", "0", ";"}, "="),
        Line(2, {"b", "=", "100", ";"}, "="),
        Line(3, {"c", "=", "50", ";"}, "="),
        Line(4, {"while", "(", "a", "<", "50", ")", "{"}, "while"),
        Line(5, {"while", "(", "b", ">", "1", ")", "{"}, "while"),
        Line(6, {"if", "(", "a", ">", "25", ")", "then", "{"}, "if"),
        Line(7, {"if", "(", "b", "<", "50", ")", "then", "{"}, "if"),
        Line(8, {"b", "=", "b", "/", "2", ";"}, "="),
        Line(9, {"a", "=", "a", "+", "5", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(10, {"if", "(", "b", "<", "75", ")", "then", "{"}, "if"),
        Line(11, {"b", "=", "b", "/", "3", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(12, {"b", "=", "b", "/", "4", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}"),
        Line({"}","else", "{"}, "else"),
        Line(13, {"a", "=", "a", "*", "2", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}"),
        Line(14, {"a", "=", "a", "+", "1", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}"),
};

const set<string> superNestedVariables = {"a", "b", "c"};

const vector<Line> readPoint = {
        Line({"procedure", "readPoint", "{"}, "procedure"),
        Line(4, {"read", "x", ";"}, "read"),
        Line(5, {"read", "y", ";"}, "read"),
        Line({"}"}, "}"),
};

const set<string> readPointVariables = {"x", "y"};

const vector<Line> program = {
        Line({"procedure", "main", "{"}, "procedure"),
        Line(1, {"flag", "=", "0", ";"}, "="),
        Line(2, {"call", "computeCentroid", ";"}, "call"),
        Line(3, {"call", "printResults", ";"}, "call"),
        Line({"}"}, "}"),
        Line({"procedure", "readPoint", "{"}, "procedure"),
        Line(4, {"read", "x", ";"}, "read"),
        Line(5, {"read", "y", ";"}, "read"),
        Line({"}"}, "}"),
        Line({"procedure", "printResults", "{"}, "procedure"),
        Line(6, {"print", "flag", ";"}, "print"),
        Line(7, {"print", "cenX", ";"}, "print"),
        Line(8, {"print", "cenY", ";"}, "print"),
        Line(9, {"print", "normSq", ";"}, "print"),
        Line({"}"}, "}"),
        Line({"procedure", "computeCentroid", "{"}, "procedure"),
        Line(10, {"count", "=", "0", ";"}, "="),
        Line(11, {"cenX", "=", "0", ";"}, "="),
        Line(12, {"cenY", "=", "0", ";"}, "="),
        Line(13, {"call", "readPoint", ";"}, "call"),
        Line(14, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, "while"),
        Line(15, {"count", "=", "count", "+", "1", ";"}, "="),
        Line(16, {"cenX", "=", "cenX", "+", "x", ";"}, "="),
        Line(17, {"cenY", "=", "cenY", "+", "y", ";"}, "="),
        Line(18, {"call", "readPoint", ";"}, "call"),
        Line({"}"}, "}"),
        Line(19, {"if", "(", "count", "==", "0", ")", "{"}, "if"),
        Line(20, {"flag", "=", "1", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, "="),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, "="),
        Line({"}"}, "}"),
        Line(23, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, "="),
        Line({"}"}, "}"),
};

const set<string> programVariables = {"flag", "x", "y", "cenX", "cenY", "normSq", "count", "normSq"};

const vector<Line> source2 = {
        Line({"procedure", "proc1", "{"}, "procedure"),
        Line(1, {"v", "=", "0", ";"}, "="),
        Line(2, {"w", "=", "0", ";"}, "="),
        Line(3, {"x", "=", "0", ";"}, "="),
        Line(4, {"y", "=", "0", ";"}, "="),
        Line(5, {"z", "=", "0", ";"}, "="),
        Line(6, {"a", "=", "1", ";"}, "="),
        Line(7, {"b", "=", "2", ";"}, "="),
        Line(8, {"c", "=", "3", ";"}, "="),
        Line(9, {"d", "=", "4", ";"}, "="),
        Line(10, {"e", "=", "5", ";"}, "="),
        Line(11, {"f", "=", "6", ";"}, "="),
        Line(12, {"v", "=", "a", "-", "b", "+", "c", ";"}, "="),
        Line(13, {"if", "(", "v", ">", "0", ")", "then", "{"}, "if"),
        Line(14, {"w", "=", "a", "-", "(", "b", "+", "c", ")", ";"}, "="),
        Line(15, {"x", "=", "a", "*", "b", "/", "c", ";"}, "="),
        Line(16, {"y", "=", "a", "*", "(", "b", "/", "c", ")", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(17, {"z", "=", "a", "+", "b", "*", "c", "*", "d", "+", "e", ";"}, "="),
        Line({"}"}, "}"),
        Line(18, {"count", "=", "0", ";"}, "="),
        Line(19, {"while", "(", "count", "<", "7", ")", "{"}, "while"),
        Line(20, {"count", "=", "count", "+", "1", ";"}, "="),
        Line({"}"}, "}"),
        Line(21, {"call", "proc2", ";"}, "call"),
        Line({"}"}, "}"),
        Line({"procedure", "proc2", "{"}, "procedure"),
        Line(22, {"w", "=", "b", "+", "c", "+", "8", ";"}, "="),
        Line(23, {"x", "=", "d", "*", "e", "", "9", ";"}, "="),
        Line({"}"}, "}")
};

const set<string> source2Variables = {"v", "w", "x", "y", "z", "a", "b", "c", "d", "e", "f", "v", "count"};

const vector<Line> source4 = {
        Line({"procedure", "proc1", "{"}, "procedure"),
        Line(1, {"a", "=", "0", ";"}, "="),
        Line(2, {"b", "=", "100", ";"}, "="),
        Line(3, {"c", "=", "50", ";"}, "="),
        Line(4, {"while", "(", "a", "<", "50", ")", "{"}, "while"),
        Line(5, {"while", "(", "b", ">", "1", ")", "{"}, "while"),
        Line(6, {"if", "(", "a", ">", "25", ")", "then", "{"}, "if"),
        Line(7, {"if", "(", "b", "<", "50", ")", "then", "{"}, "if"),
        Line(8, {"b", "=", "b", "/", "2", ";"}, "="),
        Line(9, {"a", "=", "a", "+", "5", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(10, {"if", "(", "b", "<", "75", ")", "then", "{"}, "if"),
        Line(11, {"b", "=", "b", "/", "3", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(12, {"b", "=", "b", "/", "4", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}"),
        Line({"}", "else", "{"}, "else"),
        Line(13, {"a", "=", "a", "*", "2", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}"),
        Line(14, {"a", "=", "a", "+", "1", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}")
};

const set<string> source4Variables = {"a", "b", "c"};

const vector<Line> source6 = {
        Line({"procedure", "proc1", "{"}, "procedure"),
        Line(1, {"while", "(", "a", "<", "50", ")", "{"}, "while"),
        Line(2, {"while", "(", "b", ">", "1", ")", "{"}, "while"),
        Line(3, {"if", "(", "c", ">", "25", ")", "then", "{"}, "if"),
        Line(4, {"if", "(", "d", "<", "50", ")", "then", "{"}, "if"),
        Line(5,  {"e", "=", "f", "/", "2", ";"}, "="),
        Line(6,  {"g", "=", "h", "+", "5", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(7, {"if", "(", "i", "<", "75", ")", "then", "{"}, "if"),
        Line(8, {"j", "=", "k", "/", "3", ";"}, "="),
        Line({"}", "else", "{"}, "else"),
        Line(9, {"l", "=", "m", "/", "4", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}"),
        Line({"}", "else", "{"}, "else"),
        Line(10, {"n", "=", "o", "*", "2", ";"}, "="),
        Line(11, {"p", "=", "q", ";"}),
        Line({"}"}, "}"),
        Line({"}"}, "}"),
        Line(12, {"r", "=", "s", "+", "1", ";"}, "="),
        Line({"}"}, "}"),
        Line({"}"}, "}")
};

const set<string> source6Variables = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s"};
