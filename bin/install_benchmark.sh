mkdir -p build_dir
git clone https://github.com/google/benchmark build_dir/benchmark
cd build_dir/benchmark && cmake && sudo make install && cd ../..

