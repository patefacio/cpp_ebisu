library apps;

import '../lib/fcs_installation.dart';
import 'apps/date_time_converter.dart' as date_time_converter;
import 'apps/display_csv.dart' as display_csv;
import 'apps/h5ds2csv.dart' as h5ds2csv;

addItems() {
  date_time_converter.addItems();
  display_csv.addItems();
  h5ds2csv.addItems();
}

main() {
  addItems();
  fcsInstallation.generate();
}
