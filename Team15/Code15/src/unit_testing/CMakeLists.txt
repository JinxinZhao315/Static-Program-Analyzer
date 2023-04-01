project(unitTesting)
cmake_minimum_required(VERSION 3.20.2)
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_source_processor/parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_source_processor/tokeniser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_source_processor/extractor/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_source_processor/extractor/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/models/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/utils/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/TestUtils/*.cpp"
        )
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_QPS/*/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_source_processor/parser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_source_processor/tokeniser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_source_processor/extractor/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/models/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/utils/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/TestUtils/*.h"
        )

<<<<<<< HEAD

add_executable(unit_testing ${srcs} ${headers} "src/test_QPS/test_relationship_handles/TestCallsHandler.cpp" "src/test_QPS/test_relationship_handles/TestNextHandler.cpp" "src/test_QPS/test_relationship_handles/TestAffectsHandler.cpp")

=======
add_executable(unit_testing ${srcs} ${headers})
>>>>>>> d19da07951c5bba6a63cf37f914104da7044f563

target_link_libraries(unit_testing spa)

