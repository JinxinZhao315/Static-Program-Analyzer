project(unitTesting)
cmake_minimum_required(VERSION 3.20.2)
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_qps/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_qps/*/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_sp/parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_sp/tokeniser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_sp/extractor/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_sp/extractor/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/models/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/utils/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/TestUtils/*.cpp"
        )
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_qps/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_qps/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_qps/*/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_qps/*/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_sp/parser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_sp/tokeniser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_sp/extractor/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/models/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/utils/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/TestUtils/*.h"
        )


add_executable(unit_testing ${srcs} ${headers})


target_link_libraries(unit_testing spa)

