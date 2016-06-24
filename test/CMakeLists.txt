cmake_minimum_required(VERSION 3.3)
project(alg_test)

include_directories(../src/ ../)

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

add_library(alg_test STATIC test.h test.cc time_util.h time_util.cc)

add_executable(add_long_test add_long_test.cc)
target_link_libraries(add_long_test alg_test add_long list_node)

add_executable(combinations_test combinations_test.cc)
target_link_libraries(combinations_test alg_test combinations)

add_executable(digit_count_test digit_count_test.cc)
target_link_libraries(digit_count_test alg_test digit_count)

add_executable(digit_count_generate_test_case ./digit_count_test_data/generate_test_data.cc)
target_link_libraries(digit_count_generate_test_case alg_test digit_count rand)

add_executable(dijkstra_test dijkstra_test.cc matrix.cc matrix.h)
target_link_libraries(dijkstra_test alg_test dijkstra)

add_executable(floyd_test floyd_test.cc matrix.cc matrix.h)
target_link_libraries(floyd_test alg_test floyd dijkstra)

add_executable(longest_increasing_subsequence_test longest_increasing_subsequence_test.cc)
target_link_libraries(longest_increasing_subsequence_test alg_test longest_increasing_subsequence)

add_executable(major_element_test major_element_test.cc)
target_link_libraries(major_element_test alg_test major_element)

add_executable(mtree_test mtree_test.cc)
target_link_libraries(mtree_test alg_test mtree rand)

add_executable(random_shuffle_test random_shuffle_test.cc)
target_link_libraries(random_shuffle_test alg_test random_shuffle)

add_executable(sort_test sort_test.cc)
target_link_libraries(sort_test alg_test sort)

add_executable(tree_traversal_test tree_traversal_test.cc)
target_link_libraries(tree_traversal_test alg_test tree_traversal)
