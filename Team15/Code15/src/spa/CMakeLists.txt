file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
<<<<<<< HEAD
add_library(spa ${srcs} ${headers} "src/PQLPreprocessor.cpp" "src/Utility.h" "src/Utility.cpp")
=======
add_library(spa ${srcs} ${headers})
>>>>>>> 8dcec7943a2806c7da3e1daea2a70094ed5501c1
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


