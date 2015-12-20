library apps;

import '../lib/ebisu_installation.dart';
import 'apps/date_time_converter.dart' as date_time_converter;
import 'apps/h5ds2csv.dart' as h5ds2csv;
import 'apps/qt_environment.dart' as qt_environment;

addItems() {
  date_time_converter.addItems();
  h5ds2csv.addItems();
  qt_environment.addItems();
}

main() {
  addItems();
  ebisuInstallation.generate();
}
