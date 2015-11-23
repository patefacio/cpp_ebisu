#!/bin/sh
mkdir -p build_dir
wget -O build_dir/CMake-hdf5-1.8.16.tar.gz http://www.hdfgroup.org/ftp/HDF5/current/src/CMake-hdf5-1.8.16.tar.gz
tar xvfz build_dir/CMake-hdf5-1.8.16.tar.gz -C build_dir
MY_CMAKE=$(pwd)/build_dir/cmake-3.1.0-Linux-x86_64/bin/cmake
$MY_CMAKE build_dir/CMake-hdf5-1.8.16/hdf5-1.8.16 -Bbuild_dir/CMake-hdf5-1.8.16_build
tar xvfz build_dir/CMake-hdf5-1.8.16/SZip.tar.gz -C build_dir
cd build_dir/SZip && $MY_CMAKE . && sudo make install && cd -
tar xvfz build_dir/CMake-hdf5-1.8.16/ZLib.tar.gz -C build_dir
cd build_dir/ZLib && $MY_CMAKE . && sudo make install && cd -
cd build_dir/CMake-hdf5-1.8.16_build && sudo make -j6 install && cd -

