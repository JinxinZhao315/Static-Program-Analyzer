cmake_minimum_required(VERSION 3.20.2)
project(source_processor)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(srcs ${srcs}
        src/*.h
        src/tokeniser/*.h
        src/extractor/*.h
        src/parser/*.h
        src/util/*.h
        )

set(headers ${headers}
        include/*.h
        include/tokeniser/*.h
        include/extractor/*.h
        include/parser/*.h
        include/util/*.h
        )

add_library(source_processor ${srcs} ${headers})
add_executable(SourceProcessor ${srcs} ${headers})
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(source_processor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
