#include "Constants.hpp"

const vector<Line> mainProgram = {
        Line({"procedure", "main", "{"}, PROCEDURE),
        Line(1, {"flag", "=", "0", ";"}, ASSIGN),
        Line(2, {"call", "computeCentroid", ";"}, CALL),
        Line(3, {"call", "printResults", ";"}, CALL),
        Line({"}"}, CLOSE_CURLY),
};

const set<string> mainProgramVariables = {"flag"};

const vector<Line> onlyCallStatements = {
        Line({"procedure", "main", "{"}, PROCEDURE),
        Line(2, {"call", "computeCentroid", ";"}, CALL),
        Line(3, {"call", "printResults", ";"}, CALL),
        Line({"}"}, CLOSE_CURLY),
};

const set<string> onlyCallStatementsVariables;

const vector<Line> singleAssignmentSelfIncrement = {
        Line(6, {"count", "=", "count", "+", "1", ";"}, ASSIGN)
};

const set<string> singleAssignmentSelfIncrementVariables = {"count"};

const vector<Line> singleAssignmentAddVariable = {
        Line(7, {"cenX", "=", "cenX", "+", "x", ";"}, ASSIGN)
};

const set<string> singleAssignmentAddVariableVariables = {"cenX", "x"};

const vector<Line> whileLoop = {
        Line(5, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, WHILE),
        Line(6, {"count", "=", "count", "+", "1", ";"}, ASSIGN),
        Line(7, {"cenX", "=", "cenX", "+", "x", ";"}, ASSIGN),
        Line(8, {"cenY", "=", "cenY", "+", "y", ";"}, ASSIGN),
        Line(9, {"call", "readPoint", ";"}, CALL),
        Line({"}"}, CLOSE_CURLY),
};

const set<string> whileLoopVariables = {"x", "y", "count", "cenX", "cenY"};

const vector<Line> whileLoop2 = {
        Line(4, {"call", "readPoint", ";"}, CALL),
        Line(5, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, WHILE),
        Line(6, {"count", "=", "count", "+", "1", ";"}, ASSIGN),
        Line(7, {"cenX", "=", "cenX", "+", "x", ";"}, ASSIGN),
        Line(8, {"cenY", "=", "cenY", "+", "y", ";"}, ASSIGN),
        Line(9, {"call", "readPoint", ";"}, CALL),
        Line({"}"}, CLOSE_CURLY),
        Line(10, {"call", "readPoint", ";"}, CALL),
};

const vector<Line> whileLoopInProcedure = {
        Line({"procedure", "whileLoopInProcedure", "{"}, PROCEDURE),
        Line(1, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, WHILE),
        Line(2, {"count", "=", "count", "+", "1", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY)
};

const vector<Line> whileLoopInProcedureWithLinesBeforeAfter = {
        Line({"procedure", "whileLoopInProcedure", "{"}, PROCEDURE),
        Line(1, {"count", "=", "0", ";"}, ASSIGN),
        Line(2, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, WHILE),
        Line(3, {"count", "=", "count", "+", "1", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line(4, {"call", "readPoint", ";"}, CALL),
        Line({"}"}, CLOSE_CURLY)
};

const set<string> whileLoop2Variables = {"x", "y", "count", "cenX", "cenY"};

const vector<Line> computeCentroid = {
        Line({"procedure", "computeCentroid", "{"}, PROCEDURE),
        Line(1, {"count", "=", "0", ";"}, ASSIGN),
        Line(2, {"cenX", "=", "0", ";"}, ASSIGN),
        Line(3, {"cenY", "=", "0", ";"}, ASSIGN),
        Line(4, {"call", "readPoint", ";"}, CALL),
        Line(5, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, WHILE),
        Line(6, {"count", "=", "count", "+", "1", ";"}, ASSIGN),
        Line(7, {"cenX", "=", "cenX", "+", "x", ";"}, ASSIGN),
        Line(8, {"cenY", "=", "cenY", "+", "y", ";"}, ASSIGN),
        Line(9, {"call", "readPoint", ";"}, CALL),
        Line({"}"}, CLOSE_CURLY),
        Line(10, {"if", "(", "count", "==", "0", ")", "{"}, IF),
        Line(11, {"flag", "=", "1", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(12, {"cenX", "=", "cenX", "/", "count", ";"}, ASSIGN),
        Line(13, {"cenY", "=", "cenY", "/", "count", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line(14, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
};

const set<string> computeCentroidVariables = {"x", "y", "count", "cenX", "cenY", "flag", "normSq"};

const vector<Line> ifElse = {
        Line(19, {"if", "(", "count", "==", "0", ")", "{"}, IF),
        Line(20, {"flag", "=", "1", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, ASSIGN),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
};

const vector<Line> ifElseInProcedure = {
        Line({"procedure", "ifElseInProcedure", "{"}, PROCEDURE),
        Line(1, {"flag", "=", "1", ";"}, ASSIGN),
        Line(2, {"if", "(", "count", "==", "0", ")", "{"}, IF),
        Line(3, {"flag", "=", "1", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(4, {"cenX", "=", "cenX", "/", "count", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line(5, {"flag", "=", "1", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
};

const set<string> ifElseVariables = {"count", "cenX", "cenY", "flag"};

const vector<Line> ifElse2 = {
        Line(18, {"call", "readPoint", ";"}, CALL),
        Line(19, {"if", "(", "count", "==", "0", ")", "{"}, IF),
        Line(20, {"flag", "=", "1", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, ASSIGN),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line(23, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, ASSIGN),
};

const set<string> ifElse2Variables = {"count", "cenX", "cenY", "flag", "normSq"};

const vector<Line> superNested = {
        Line({"procedure", "proc1", "{"}, PROCEDURE),
        Line(1, {"a", "=", "0", ";"}, ASSIGN),
        Line(2, {"b", "=", "100", ";"}, ASSIGN),
        Line(3, {"c", "=", "50", ";"}, ASSIGN),
        Line(4, {"while", "(", "a", "<", "50", ")", "{"}, WHILE),
        Line(5, {"while", "(", "b", ">", "1", ")", "{"}, WHILE),
        Line(6, {"if", "(", "a", ">", "25", ")", "then", "{"}, IF),
        Line(7, {"if", "(", "b", "<", "50", ")", "then", "{"}, IF),
        Line(8, {"b", "=", "b", "/", "2", ";"}, ASSIGN),
        Line(9, {"a", "=", "a", "+", "5", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(10, {"if", "(", "b", "<", "75", ")", "then", "{"}, IF),
        Line(11, {"b", "=", "b", "/", "3", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(12, {"b", "=", "b", "/", "4", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY),
        Line({"}","else", "{"}, ELSE),
        Line(13, {"a", "=", "a", "*", "2", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY),
        Line(14, {"a", "=", "a", "+", "1", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY),
};

const set<string> superNestedVariables = {"a", "b", "c"};

const vector<Line> readPoint = {
        Line({"procedure", "readPoint", "{"}, PROCEDURE),
        Line(4, {"read", "x", ";"}, READ),
        Line(5, {"read", "y", ";"}, READ),
        Line({"}"}, CLOSE_CURLY),
};

const set<string> readPointVariables = {"x", "y"};

const vector<Line> program = {
        Line({"procedure", "main", "{"}, PROCEDURE),
        Line(1, {"flag", "=", "0", ";"}, ASSIGN),
        Line(2, {"call", "computeCentroid", ";"}, CALL),
        Line(3, {"call", "printResults", ";"}, CALL),
        Line({"}"}, CLOSE_CURLY),
        Line({"procedure", "readPoint", "{"}, PROCEDURE),
        Line(4, {"read", "x", ";"}, READ),
        Line(5, {"read", "y", ";"}, READ),
        Line({"}"}, CLOSE_CURLY),
        Line({"procedure", "printResults", "{"}, PROCEDURE),
        Line(6, {"print", "flag", ";"}, PRINT),
        Line(7, {"print", "cenX", ";"}, PRINT),
        Line(8, {"print", "cenY", ";"}, PRINT),
        Line(9, {"print", "normSq", ";"}, PRINT),
        Line({"}"}, CLOSE_CURLY),
        Line({"procedure", "computeCentroid", "{"}, PROCEDURE),
        Line(10, {"count", "=", "0", ";"}, ASSIGN),
        Line(11, {"cenX", "=", "0", ";"}, ASSIGN),
        Line(12, {"cenY", "=", "0", ";"}, ASSIGN),
        Line(13, {"call", "readPoint", ";"}, CALL),
        Line(14, {"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{"}, WHILE),
        Line(15, {"count", "=", "count", "+", "1", ";"}, ASSIGN),
        Line(16, {"cenX", "=", "cenX", "+", "x", ";"}, ASSIGN),
        Line(17, {"cenY", "=", "cenY", "+", "y", ";"}, ASSIGN),
        Line(18, {"call", "readPoint", ";"}, CALL),
        Line({"}"}, CLOSE_CURLY),
        Line(19, {"if", "(", "count", "==", "0", ")", "{"}, IF),
        Line(20, {"flag", "=", "1", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(21, {"cenX", "=", "cenX", "/", "count", ";"}, ASSIGN),
        Line(22, {"cenY", "=", "cenY", "/", "count", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line(23, {"normSq", "=", "cenX", "*", "cenX", "+", "cenY", "*", "cenY", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
};

const set<string> programVariables = {"flag", "x", "y", "cenX", "cenY", "normSq", "count", "normSq"};

const vector<Line> source2 = {
        Line({"procedure", "proc1", "{"}, PROCEDURE),
        Line(1, {"v", "=", "0", ";"}, ASSIGN),
        Line(2, {"w", "=", "0", ";"}, ASSIGN),
        Line(3, {"x", "=", "0", ";"}, ASSIGN),
        Line(4, {"y", "=", "0", ";"}, ASSIGN),
        Line(5, {"z", "=", "0", ";"}, ASSIGN),
        Line(6, {"a", "=", "1", ";"}, ASSIGN),
        Line(7, {"b", "=", "2", ";"}, ASSIGN),
        Line(8, {"c", "=", "3", ";"}, ASSIGN),
        Line(9, {"d", "=", "4", ";"}, ASSIGN),
        Line(10, {"e", "=", "5", ";"}, ASSIGN),
        Line(11, {"f", "=", "6", ";"}, ASSIGN),
        Line(12, {"v", "=", "a", "-", "b", "+", "c", ";"}, ASSIGN),
        Line(13, {"if", "(", "v", ">", "0", ")", "then", "{"}, IF),
        Line(14, {"w", "=", "a", "-", "(", "b", "+", "c", ")", ";"}, ASSIGN),
        Line(15, {"x", "=", "a", "*", "b", "/", "c", ";"}, ASSIGN),
        Line(16, {"y", "=", "a", "*", "(", "b", "/", "c", ")", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(17, {"z", "=", "a", "+", "b", "*", "c", "*", "d", "+", "e", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line(18, {"count", "=", "0", ";"}, ASSIGN),
        Line(19, {"while", "(", "count", "<", "7", ")", "{"}, WHILE),
        Line(20, {"count", "=", "count", "+", "1", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line(21, {"call", "proc2", ";"}, CALL),
        Line({"}"}, CLOSE_CURLY),
        Line({"procedure", "proc2", "{"}, PROCEDURE),
        Line(22, {"w", "=", "b", "+", "c", "+", "8", ";"}, ASSIGN),
        Line(23, {"x", "=", "d", "*", "e", "", "9", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY)
};

const set<string> source2Variables = {"v", "w", "x", "y", "z", "a", "b", "c", "d", "e", "f", "v", "count"};

const vector<Line> source4 = {
        Line({"procedure", "proc1", "{"}, PROCEDURE),
        Line(1, {"a", "=", "0", ";"}, ASSIGN),
        Line(2, {"b", "=", "100", ";"}, ASSIGN),
        Line(3, {"c", "=", "50", ";"}, ASSIGN),
        Line(4, {"while", "(", "a", "<", "50", ")", "{"}, WHILE),
        Line(5, {"while", "(", "b", ">", "1", ")", "{"}, WHILE),
        Line(6, {"if", "(", "a", ">", "25", ")", "then", "{"}, IF),
        Line(7, {"if", "(", "b", "<", "50", ")", "then", "{"}, IF),
        Line(8, {"b", "=", "b", "/", "2", ";"}, ASSIGN),
        Line(9, {"a", "=", "a", "+", "5", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(10, {"if", "(", "b", "<", "75", ")", "then", "{"}, IF),
        Line(11, {"b", "=", "b", "/", "3", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(12, {"b", "=", "b", "/", "4", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY),
        Line({"}", "else", "{"}, ELSE),
        Line(13, {"a", "=", "a", "*", "2", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY),
        Line(14, {"a", "=", "a", "+", "1", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY)
};

const set<string> source4Variables = {"a", "b", "c"};

const vector<Line> source6 = {
        Line({"procedure", "proc1", "{"}, PROCEDURE),
        Line(1, {"while", "(", "a", "<", "50", ")", "{"}, WHILE),
        Line(2, {"while", "(", "b", ">", "1", ")", "{"}, WHILE),
        Line(3, {"if", "(", "c", ">", "25", ")", "then", "{"}, IF),
        Line(4, {"if", "(", "d", "<", "50", ")", "then", "{"}, IF),
        Line(5,  {"e", "=", "f", "/", "2", ";"}, ASSIGN),
        Line(6,  {"g", "=", "h", "+", "5", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(7, {"if", "(", "i", "<", "75", ")", "then", "{"}, IF),
        Line(8, {"j", "=", "k", "/", "3", ";"}, ASSIGN),
        Line({"}", "else", "{"}, ELSE),
        Line(9, {"l", "=", "m", "/", "4", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY),
        Line({"}", "else", "{"}, ELSE),
        Line(10, {"n", "=", "o", "*", "2", ";"}, ASSIGN),
        Line(11, {"p", "=", "q", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY),
        Line(12, {"r", "=", "s", "+", "1", ";"}, ASSIGN),
        Line({"}"}, CLOSE_CURLY),
        Line({"}"}, CLOSE_CURLY)
};

const set<string> source6Variables = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s"};
