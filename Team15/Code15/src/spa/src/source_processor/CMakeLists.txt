cmake_minimum_required(VERSION 3.24)
project(source_processor)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(srcs ${srcs}
        src/SourceProcessor.cpp
        src/tokeniser/Tokeniser.cpp
        src/extractor/Extractor.cpp
        src/parser/Parser.cpp)

set(headers ${headers}
        include/SourceProcessor.h
        include/tokeniser/Tokeniser.h
        include/extractor/Extractor.h
        include/parser/Parser.h)

add_library(source_processor ${srcs} ${headers})
add_executable(SourceProcessor ${srcs} ${headers})
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(source_processor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
