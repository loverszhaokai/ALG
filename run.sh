#!/bin/bash

mkdir -p build-cmake/Debug/
cmake -H. -B./build-cmake/Debug/obj -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build-cmake/Debug/obj -- -j4
