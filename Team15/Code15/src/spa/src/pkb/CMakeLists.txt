cmake_minimum_required(VERSION 3.20.2)
project(pkb)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(srcs ${srcs}
        src/pkb.cpp
        src/table/*.cpp
        )

set(headers ${headers}
        include/pkb.h
        include/table/*.h
        )

add_library(pkb ${srcs} ${headers})
add_executable(pkb ${srcs} ${headers})
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(pkb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)