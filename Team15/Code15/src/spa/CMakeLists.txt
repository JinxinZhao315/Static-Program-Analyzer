cmake_minimum_required(VERSION 3.20.2)
project(spa)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/src/models/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/src/utils/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/src/evaluator/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/src/model/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/src/tokenizer/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/src/extractor/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/src/parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/src/tokeniser/*.cpp"
    )

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/include/models/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/include/utils/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/include/evaluator/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/include/model/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/include/tokenizer/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/include/hasher/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/include/table/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/include/extractor/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/include/parser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/include/tokeniser/*.h"
    )


add_library(spa ${srcs} ${headers} src/sp/src/extractor/AffectsRelationshipExtractor.cpp src/sp/include/extractor/AffectsRelationshipExtractor.h "src/qps/include/tokenizer/QueryEvalSeqOptimizer.h" "src/qps/src/tokenizer/QueryEvalSeqOptimizer.cpp")


target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)