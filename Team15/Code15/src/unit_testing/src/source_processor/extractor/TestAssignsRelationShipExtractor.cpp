#include "catch.hpp"
#include "source_processor/include/extractor/Extractor.h"

TEST_CASE("Converting to postfix") {
    vector<string> tokens = {"1","+","2"};
    set<string> variables;
    variables.insert("a");
    variables.insert("b");
    auto result = convertToPostfix(tokens, variables);
    vector<string> expected = {"1","2","+"};
    assert(result == expected);
}