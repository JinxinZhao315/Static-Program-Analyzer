project(unitTesting)
cmake_minimum_required(VERSION 3.20.2)
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/tokeniser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/extractor/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/models/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/utils/*.cpp"
        )
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/parser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/tokeniser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/source_processor/extractor/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/models/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/utils/*.h"
        )


add_executable(unit_testing ${srcs})

target_link_libraries(unit_testing spa)

