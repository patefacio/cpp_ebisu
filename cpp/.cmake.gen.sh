#!/bin/bash
# custom <additional exports>

CMAKE=${CMAKE-`which cmake`}

export CC=gcc
export CXX=g++

#export CC=clang
#export CXX=clang++


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
