mkdir -p build_dir
wget -O build_dir/mongodb-linux-x86_64-2.4.14.tgz http://downloads.mongodb.org/cxx-driver/mongodb-linux-x86_64-2.4.14.tgz?_ga=1.219143706.2012223159.1446993713
tar xvzf build_dir/mongodb-linux-x86_64-2.4.14.tgz -C build_dir
cd build_dir/mongodb-linux-x86_64-2.4.14 && scons && sudo scons install && cd -

