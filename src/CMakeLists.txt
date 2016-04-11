cmake_minimum_required(VERSION 3.3)
project(src)

add_definitions(-D__STDC_CONSTANT_MACROS
        -D__STDC_FORMAT_MACROS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions \
    -fno-threadsafe-statics -std=c++11 -fvisibility-inlines-hidden \
    -std=gnu++11 -m64 -march=x86-64 -fvisibility=hidden -fPIC")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -D_DEBUG")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 \
    -DDYNAMIC_ANNOTATIONS_ENABLED=0 -DNDEBUG -DNVALGRIND")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
ELSE(CMAKE_BUILD_TYPE MATCHES Debug)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

IF(CMAKE_BUILD_ASAN_TYPE MATCHES 1)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
        -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lasan")
ENDIF(CMAKE_BUILD_ASAN_TYPE MATCHES 1)


add_subdirectory(util)


add_library(add_long STATIC add_long.cc add_long.h)

add_library(combinations STATIC combinations.cc combinations.h)

add_library(dijkstra STATIC dijkstra.cc dijkstra.h)

add_library(floyd STATIC floyd.cc floyd.h)

add_library(list_node STATIC list_node.cc list_node.h)

add_library(longest_increasing_subsequence STATIC
            longest_increasing_subsequence.cc
            longest_increasing_subsequence.h)

add_library(major_element STATIC major_element.cc major_element.h)

add_library(random_shuffle STATIC random_shuffle.cc)
target_link_libraries(random_shuffle rand)

add_library(sort STATIC sort.cc sort.h)

add_library(tree_traversal STATIC tree_traversal.cc tree_traversal.h tree.h)
