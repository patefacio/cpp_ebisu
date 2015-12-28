#!/bin/bash
# custom <additional exports>

#export CC=clang
#export CXX=clang++

export CC=gcc-4.9
export CXX=g++-4.9

# end <additional exports>

cmake -DCMAKE_PREFIX_PATH=/usr/include/qt5 -DCMAKE_BUILD_TYPE=Release -B../cmake_build/release -H.
cmake -DCMAKE_PREFIX_PATH=/usr/include/qt5 -DCMAKE_BUILD_TYPE=Debug -B../cmake_build/debug -H.
