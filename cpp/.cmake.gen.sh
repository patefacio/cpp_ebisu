# custom <additional exports>

#export CC=clang
#export CXX=clang++
#export CC=gcc
#export CXX=g++

# end <additional exports>

cmake -DCMAKE_BUILD_TYPE=Release -B../cmake_build/release -H.
cmake -DCMAKE_BUILD_TYPE=Debug -B../cmake_build/debug -H.
