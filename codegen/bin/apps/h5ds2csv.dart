library bin.h5ds2csv;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final h5ds2csv = app('h5ds2csv')
  ..descr = 'Converts data_sets in hdf5 files to csv'
  ..namespace = namespace(['ebisu'])
  ..hasLogLevel = true
  ..hasSignalHandler = false
  ..hasQuitLoop = false
  ..args = [
    arg('data_set')
    ..descr = 'Name of data_set to make into csv'
    ..shortName = 'd'
    ..isMultiple = true,
    arg('input_file')
    ..descr = 'Name of hdf5 file containing data_set(s)'
    ..shortName = 'i'
    ..isMultiple = true
    ..isRequired = true,
    arg('output_file')
    ..descr = 'Name of hdf5 file containing data_set(s)'
    ..shortName = 'o',
  ];

addItems() => ebisuInstallation.addApp(h5ds2csv);

main() {
  addItems();
  ebisuInstallation.generate();
}