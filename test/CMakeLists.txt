cmake_minimum_required(VERSION 3.3)
project(alg_test)

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

add_executable(random_shuffle_test random_shuffle_test.cc)
target_link_libraries(random_shuffle_test alg_test random_shuffle)
