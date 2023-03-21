//#include "catch.hpp"
//#include "source_processor/include/parser/Parser.h"
//
//#if __APPLE__
//    string sourceProgram = "Team15/Tests15/Sample_source.txt";
//    string parsedProgram = "Team15/Tests15/Sample_source_parsed.txt";
//    string sourceProgram2 = "Team15/Tests15/Sample_source2.txt";
//    string parsedProgram2 = "Team15/Tests15/Sample_source2_parsed.txt";
//    string sourceProgram4 = "Team15/Tests15/source4.txt";
//    string parsedProgram4 = "Team15/Tests15/source4_parsed.txt";
//#elif _WIN32
//    string sourceProgram = "./Team15/Tests15/Sample_source.txt";
//    string parsedProgram = "./Team15/Tests15/Sample_source_parsed.txt";
//    string sourceProgram2 = "./Team15/Tests15/Sample_source2.txt";
//    string parsedProgram2 = "./Team15/Tests15/Sample_source2_parsed.txt";
//    string sourceProgram4 = "./Team15/Tests15/source4.txt";
//    string parsedProgram4 = "./Team15/Tests15/source4_parsed.txt";
//#endif
//
//TEST_CASE("parseProgram_emptyString_shouldReturnEmptyString") {
//    Parser parser;
//    parser.getParsedProgram();
//    vector<string> expected;
//    REQUIRE(parser.getParsedProgram() == expected);
//}
//
//TEST_CASE("parseProgram_manyProcedures_shouldReturnParsedProgram") {
//    Parser parser;
//    parser.parseProgram(sourceProgram);
//    parser.getParsedProgram();
//    vector<string> expected;
//    std::ifstream file(parsedProgram);
//    if (file.is_open()) {
//        string line;
//        while (getline(file, line)) {
//            expected.push_back(line);
//        }
//        file.close();
//    }
//    REQUIRE(parser.getParsedProgram() == expected);
//}
//
//TEST_CASE("parseProgram_oneProcedure_shouldReturnParsedProgram") {
//    Parser parser;
//    parser.parseProgram(sourceProgram2);
//    parser.getParsedProgram();
//    vector<string> expected;
//    std::ifstream file(parsedProgram2);
//    if (file.is_open()) {
//        string line;
//        while (getline(file, line)) {
//            expected.push_back(line);
//        }
//        file.close();
//    }
//    REQUIRE(parser.getParsedProgram() == expected);
//}
//
//TEST_CASE("parseProgram_oneProcedure_shouldReturnParsedProgram 2") {
//    Parser parser;
//    parser.parseProgram(sourceProgram4);
//    parser.getParsedProgram();
//    vector<string> expected;
//    std::ifstream file(parsedProgram4);
//    if (file.is_open()) {
//        string line;
//        while (getline(file, line)) {
//            expected.push_back(line);
//        }
//        file.close();
//    }
//    REQUIRE(parser.getParsedProgram() == expected);
//}
