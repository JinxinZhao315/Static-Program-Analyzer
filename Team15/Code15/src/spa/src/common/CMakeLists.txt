cmake_minimum_required(VERSION 3.20.2)
project(common)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(srcs ${srcs}
        src/models/*.cpp
        src/utils/*.cpp
    )

set(headers ${headers}
        include/models/*.h
        include/utils/*.h
    )

add_library(common ${srcs} ${headers})
add_executable(CommonExec ${srcs} ${headers})
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)