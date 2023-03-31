cmake_minimum_required(VERSION 3.20.2)
project(spa)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/src/models/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/src/utils/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/evaluator/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/model/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/tokenizer/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/extractor/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/tokeniser/*.cpp"
    )

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/include/models/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/include/utils/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/evaluator/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/model/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/tokenizer/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/include/hasher/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/include/table/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/include/extractor/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/include/parser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/include/tokeniser/*.h"
    )

add_library(spa ${srcs} ${headers} src/source_processor/src/extractor/AffectsRelationshipExtractor.cpp src/source_processor/include/extractor/AffectsRelationshipExtractor.h)

target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)