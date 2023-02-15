cmake_minimum_required(VERSION 3.24)
project(source_processor)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(srcs ${srcs}
        src/SourceProcessor.cpp
        src/tokeniser/Tokeniser.cpp
        src/extractor/Extractor.cpp
        src/parser/Parser.cpp
        src/parser/Line.cpp
        src/parser/StatementParser.cpp
        src/extractor/FollowsRelationshipExtractor.cpp
        src/extractor/ParentsRelationshipExtractor.cpp)

set(headers ${headers}
        include/SourceProcessor.h
        include/tokeniser/Tokeniser.h
        include/extractor/Extractor.h
        include/parser/Parser.h
        include/parser/Line.h
        include/parser/StatementParser.h
        include/extractor/FollowsRelationshipExtractor.h
        include/extractor/ParentsRelationshipExtractor.h)

add_library(source_processor ${srcs} ${headers} src/extractor/AssignsRelationshipExtractor.cpp include/extractor/AssignsRelationshipExtractor.h src/extractor/ModifiesRelationshipExtractor.cpp include/extractor/ModifiesRelationshipExtractor.h src/util/StringOperations.cpp include/util/StringOperations.h src/extractor/UsesRelationshipExtractor.cpp include/extractor/UsesRelationshipExtractor.h)
add_executable(SourceProcessor ${srcs} ${headers})
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(source_processor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
