#include "source_processor/include/parser/Tokeniser.h"
#include "catch.hpp"

TEST_CASE("tokeniser single procedure extraction successful test") {
Tokeniser *tokeniser = new Tokeniser();
tokeniser->tokenise("procedure example { }", 1);
string result = "";
for(string c : *tokeniser->getProcedures()) {
result += c;
}
assert(result == "example");
}

TEST_CASE("tokeniser multiple procedure extraction successful test") {
Tokeniser *tokeniser = new Tokeniser();
tokeniser->tokenise("procedure example1 { }\nprocedure example2 { }", 1);
string result = "";
for(string c : *tokeniser->getProcedures()) {
result += c + ", ";
}
assert(result == "example1, example2, ");
}

TEST_CASE("tokeniser variable extraction successful test") {
Tokeniser *tokeniser = new Tokeniser();
vector<string> tokens =  tokeniser->tokenise("procedure example {\n x = 1;\n y = 2;\n }", 1);
string result = "";
for(string c : *tokeniser->getVariables()) {
result += c + ", ";
}
assert(result == "x, y, ");
}

TEST_CASE("tokeniser constant extraction successful test") {
Tokeniser *tokeniser = new Tokeniser();
tokeniser->tokenise("procedure example {\n x = 1;\n y = 2;\n }", 1);
string result = "";
for(string c : *tokeniser->getConstants()) {
result += c + ", ";
}
assert(result == "1, 2, ");
}

TEST_CASE("tokeniser statement extraction successful test") {
Tokeniser *tokeniser = new Tokeniser();
tokeniser->tokenise("procedure example {\n x = 1;\n y = 2;\n read z;\n}", 1);
string statementsResults = "";
for (const auto& [keyword, statements] : *tokeniser->getStatements()) {
statementsResults += to_string(keyword) + ":";
for(int i : statements) {
statementsResults += to_string(i);
}
}
assert(statementsResults == "9:1110:1");
}

TEST_CASE("tokeniser variable extraction with double equals successful test") {
Tokeniser *tokeniser = new Tokeniser();
std::vector<std::string> tokens = tokeniser->tokenise("procedure example { x = 1; y == 2;}", 1);
string result = "";
for(string c : *tokeniser->getVariables()) {
result += c;
}
assert(result == "x");
}

TEST_CASE("tokeniser variable extraction with read keyword successful test") {
Tokeniser *tokeniser = new Tokeniser();
std::vector<std::string> tokens = tokeniser->tokenise("procedure example { x = 1; y == 2; read z;}", 1);
string result = "";
for(string c : *tokeniser->getVariables()) {
result += c + ", ";
}
assert(result == "x, z, ");
}

TEST_CASE("tokeniser variable extraction with double equals and no spaces successful test") {
Tokeniser *tokeniser = new Tokeniser();
std::vector<std::string> tokens = tokeniser->tokenise(" {y==2;}", 1);
string result = "";
for(string c : *tokeniser->getVariables()) {
cout << c << endl;
}
assert(result == "");
}