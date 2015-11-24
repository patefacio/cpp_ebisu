SCRIPT=$(readlink -f "$0")
BUILD_DIR=$(dirname $(dirname "$SCRIPT"))/build_dir
mkdir -p $BUILD_DIR
wget --no-check-certificate -O $BUILD_DIR/cmake-3.1.0-Linux-x86_64.tar.gz http://www.cmake.org/files/v3.1/cmake-3.1.0-Linux-x86_64.tar.gz
tar xvfz $BUILD_DIR/cmake-3.1.0-Linux-x86_64.tar.gz -C $BUILD_DIR

