<<<<<<< HEAD
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/relationship_handlers/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/relationship_handlers/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} "src/relationship_handlers/ParentHandler.h" "src/relationship_handlers/ModifiesHandler.h" "src/relationship_handlers/ModifiesHandler.cpp")
=======
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/relationship_handlers/*.cpp"
        )

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/relationship_handlers/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_library(spa ${srcs} ${headers})
>>>>>>> eac2749300d94599e06342a54ea04939e55d71cf
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


