cmake_minimum_required(VERSION 3.20.2)
project(qps)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(srcs ${srcs}
        src/PQLDriver.cpp
        src/tokenizer/*.cpp
        src/model/*.cpp
        src/evaluator/*.cpp
        )

set(headers ${headers}
        include/PQLDriver.h
        include/tokenizer/*.h
        include/model/*.h
        include/evaluator/*.h
        )

add_library(qps ${srcs} ${headers})
add_executable(qps ${srcs} ${headers})
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(qps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)