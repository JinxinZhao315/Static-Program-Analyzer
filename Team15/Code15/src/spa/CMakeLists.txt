file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/relationship_handlers/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/relationship_handlers/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} "src/FollowsTable.h" "src/FollowsTable.cpp" "src/EntityStorage.h" "src/FollowsStarTable.h" "src/FollowsStarTable.cpp")
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


