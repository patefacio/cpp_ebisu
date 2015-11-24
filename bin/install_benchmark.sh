SCRIPT=$(readlink -f "$0")
BUILD_DIR=$(dirname $(dirname "$SCRIPT"))/build_dir
mkdir -p $BUILD_DIR
MY_CMAKE=$BUILD_DIR/cmake-3.1.0-Linux-x86_64/bin/cmake
git clone https://github.com/google/benchmark $BUILD_DIR/benchmark
cd $BUILD_DIR/benchmark && $MY_CMAKE . && sudo make install && cd -

