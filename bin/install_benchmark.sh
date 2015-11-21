mkdir -p build_dir
MY_CMAKE=$(pwd)/build_dir/cmake-3.1.0-Linux-x86_64/bin/cmake
git clone https://github.com/google/benchmark build_dir/benchmark
cd build_dir/benchmark && $MY_CMAKE . && sudo make install && cd -

