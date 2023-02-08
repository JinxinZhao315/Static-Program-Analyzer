cmake_minimum_required(VERSION 3.24)
project(SourceProcessor)
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/design_extractor/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/tokeniser/*.cpp")
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/design_extractor/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/parser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/tokeniser/*.cpp")
add_library(source_processor ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(source_processor PUBLIC include)
add_executable(${PROJECT_NAME} src/SourceProcessor.cpp include/SourceProcessor.h)
target_link_libraries(source_processor)