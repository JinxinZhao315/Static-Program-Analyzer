file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/evaluator/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/model/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/src/tokenizer/*.cpp"
        )

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/evaluator/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/model/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/include/tokenizer/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_library(spa ${srcs} ${headers} "src/QPS/src/model/SynonymLinkageMap.cpp" "src/QPS/include/model/SynonymLinkageMap.h")

# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


