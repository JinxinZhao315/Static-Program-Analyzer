file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/test_relationship_handles/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/test_relationship_handles/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/test_relationship_handles/*.hpp")
add_executable(unit_testing ${srcs} "src/test_relationship_handles/TestModifiesSHandler.cpp" "src/test_relationship_handles/TestParentHandler.cpp")

target_link_libraries(unit_testing spa)

