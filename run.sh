#!/bin/bash

autoreconf --install
./configure
make clean
make -sj8
make check
