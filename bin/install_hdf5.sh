SCRIPT=$(readlink -f "$0")
BUILD_DIR=$(dirname $(dirname "$SCRIPT"))/build_dir
mkdir -p $BUILD_DIR
wget -O $BUILD_DIR/CMake-hdf5-1.8.16.tar.gz http://www.hdfgroup.org/ftp/HDF5/current/src/CMake-hdf5-1.8.16.tar.gz
tar xvfz $BUILD_DIR/CMake-hdf5-1.8.16.tar.gz -C $BUILD_DIR
MY_CMAKE=$BUILD_DIR/cmake-3.1.0-Linux-x86_64/bin/cmake
$MY_CMAKE $BUILD_DIR/CMake-hdf5-1.8.16/hdf5-1.8.16 -B$BUILD_DIR/CMake-hdf5-1.8.16_build
tar xvfz $BUILD_DIR/CMake-hdf5-1.8.16/SZip.tar.gz -C $BUILD_DIR
cd $BUILD_DIR/SZip && $MY_CMAKE . && sudo make install && cd -
tar xvfz $BUILD_DIR/CMake-hdf5-1.8.16/ZLib.tar.gz -C $BUILD_DIR
cd $BUILD_DIR/ZLib && $MY_CMAKE . && sudo make install && cd -
cd $BUILD_DIR/CMake-hdf5-1.8.16_build && sudo make -j6 install && cd -

