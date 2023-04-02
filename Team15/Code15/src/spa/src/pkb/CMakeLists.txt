cmake_minimum_required(VERSION 3.20.2)
project(pkb)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(srcs ${srcs}
        src/pkb.cpp
        )

set(headers ${headers}
        include/pkb.h
        include/hasher/*.h
        include/table/*.h
        )

add_library(pkb ${srcs} ${headers})
add_executable(pkb ${srcs} ${headers})
target_include_directories(pkb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)