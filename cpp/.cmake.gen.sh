#!/bin/bash
# custom <additional exports>

#export CC=clang
#export CXX=clang++

export CC=gcc-4.9
export CXX=g++-4.9

# end <additional exports>

$CMAKE \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_PREFIX_PATH=/usr/include/qt5 \
  -B../cmake_build/release \
  -H.

$CMAKE \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_PREFIX_PATH=/usr/include/qt5 \
  -B../cmake_build/debug \
  -H.
