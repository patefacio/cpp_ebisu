SCRIPT=$(readlink -f "$0")
BUILD_DIR=$(dirname $(dirname "$SCRIPT"))/build_dir
mkdir -p $BUILD_DIR
git clone https://github.com/mongodb/mongo-cxx-driver.git $BUILD_DIR/mongo-cxx-driver
cd $BUILD_DIR/mongo-cxx-driver && sudo scons --prefix=/opt/mongo-client-install install && cd -

