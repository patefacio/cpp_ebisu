SCRIPT=$(readlink -f "$0")
BUILD_DIR=$(dirname $(dirname "$SCRIPT"))/build_dir
mkdir -p $BUILD_DIR
export VERSION=1.10.0
wget -O $BUILD_DIR/CMake-hdf5-$VERSION.tar.gz http://www.hdfgroup.org/ftp/HDF5/current/src/CMake-hdf5-$VERSION-patch1.tar.gz
tar xvfz $BUILD_DIR/CMake-hdf5-$VERSION.tar.gz -C $BUILD_DIR
MY_CMAKE=$BUILD_DIR/cmake-3.4.0-Linux-x86_64/bin/cmake
$MY_CMAKE $BUILD_DIR/CMake-hdf5-$VERSION-patch1/hdf5-$VERSION-patch1 -B$BUILD_DIR/CMake-hdf5-$VERSION_build
tar xvfz $BUILD_DIR/CMake-hdf5-$VERSION-patch1/SZip.tar.gz -C $BUILD_DIR
cd $BUILD_DIR/SZip && $MY_CMAKE . && sudo make install && cd -
tar xvfz $BUILD_DIR/CMake-hdf5-$VERSION-patch1/ZLib.tar.gz -C $BUILD_DIR
cd $BUILD_DIR/ZLib && $MY_CMAKE . && sudo make install && cd -
cd $BUILD_DIR/CMake-hdf5-$VERSION_build && sudo make -j6 install && cd -

