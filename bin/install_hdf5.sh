mkdir -p build_dir
wget -O build_dir/CMake-hdf5-1.8.16.tar.gz http://www.hdfgroup.org/ftp/HDF5/current/src/CMake-hdf5-1.8.16.tar.gz
tar xvfz build_dir/CMake-hdf5-1.8.16.tar.gz -C build_dir
build_dir/cmake-3.1.0-Linux-x86_64/bin/cmake build_dir/CMake-hdf5-1.8.16/hdf5-1.8.16 -Bbuild_dir/CMake-hdf5-1.8.16_build
cd build_dir/CMake-hdf5-1.8.16_build && make install

