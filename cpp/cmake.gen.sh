# custom <additional exports>
export CC=$HOME/install/llvm31/bin/clang
export CXX=$HOME/install/llvm31/bin/clang++
# end <additional exports>

cmake -DCMAKE_BUILD_TYPE=Release -B../cmake_build/release -H.
cmake -DCMAKE_BUILD_TYPE=Debug -B../cmake_build/debug -H.
