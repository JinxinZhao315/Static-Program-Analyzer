file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/test_relationship_handles/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/test_relationship_headles/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/test_relationship_headles/*.hpp")
add_executable(unit_testing ${srcs})

target_link_libraries(unit_testing spa)

