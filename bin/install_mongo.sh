SCRIPT=$(readlink -f "$0")
BUILD_DIR=$(dirname $(dirname "$SCRIPT"))/build_dir
mkdir -p $BUILD_DIR
MY_CMAKE=$BUILD_DIR/cmake-3.4.0-Linux-x86_64/bin/cmake
git clone -b master https://github.com/mongodb/mongo-c-driver.git $BUILD_DIR/mongo-c-driver
git clone https://github.com/mongodb/mongo-cxx-driver.git $BUILD_DIR/mongo-cxx-driver
pushd $BUILD_DIR/mongo-c-driver; ./autogen.sh --enable-tests=no --enable-examples=no --with-libbson=bundled; make; sudo make install; popd;
pushd $BUILD_DIR/mongo-cxx-driver && $MY_CMAKE . && sudo make install && cd -; popd

