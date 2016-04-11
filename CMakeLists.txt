cmake_minimum_required(VERSION 3.3)
project(ALG)

# usage
# debug
# 1 enter baseparser dir
# 2 make output dir: e.g. build-cmake/Debug
# 3 exec: cmake -H. -B./build-cmake/Debug/obj -DCMAKE_BUILD_TYPE=Debug
# 3.1 build with asan and debug: cmake -H. -B./build-cmake/Debug/obj -DCMAKE_BUILD_TYPE=Debug -DCMAKE_BUILD_ASAN_TYPE=1
# 4 build target: cmake --build ./build-cmake/Debug/obj -- -j4
# 5 clean: cmake --build ./build-cmake/Debug --target clean

# release
# 1 enter baseparser dir
# 2 make output dir: e.g. build-cmake/Release
# 3 exec: cmake -H. -B./build-cmake/Release/obj -DCMAKE_BUILD_TYPE=Release
# 4 build target: cmake --build ./build-cmake/Release/obj -- -j4
# 5 clean: cmake --build ./build-cmake/Release --target clean
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# add to settings: -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_C_COMPILER="/usr/bin/clang" -DCMAKE_CXX_COMPILER="/usr/bin/clang++"
#set(CMAKE_C_COMPILER "/usr/bin/clang")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_VERBOSE_MAKEFILE ON)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build-cmake/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build-cmake/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build-cmake/${CMAKE_BUILD_TYPE}/lib)

add_subdirectory(src)
add_subdirectory(test)
