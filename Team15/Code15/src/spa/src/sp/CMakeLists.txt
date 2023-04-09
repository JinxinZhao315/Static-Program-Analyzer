cmake_minimum_required(VERSION 3.20.2)
project(sp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(srcs ${srcs}
        src/SourceProcessor.cpp
        src/tokeniser/*.cpp
        src/extractor/*.cpp
        src/parser/*.cpp
    )

set(headers ${headers}
        include/SourceProcessor.h
        include/tokeniser/*.h
        include/extractor/*.h
        include/parser/*.h
    )

add_library(sp ${srcs} ${headers})
add_executable(sp ${srcs} ${headers})
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(sp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
