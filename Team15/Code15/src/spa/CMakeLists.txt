file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/evaluator/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/model/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/tokenizer/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/src/table/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/extractor/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/tokeniser/*.cpp"
        "src/util/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/extractor/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/src/tokeniser/*.cpp"
        "src/util/*.cpp"
        )

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/evaluator/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/model/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/tokenizer/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/include/table/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/include/extractor/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/include/parser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/include/tokeniser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/include/util/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_library(spa ${srcs} ${headers})

# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


