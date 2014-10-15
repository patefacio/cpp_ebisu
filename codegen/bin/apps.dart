library apps;

import '../lib/installation.dart';
import 'apps/date_time_converter.dart' as date_time_converter;
import 'apps/display_csv.dart' as display_csv;

addItems() {
  date_time_converter.addItems();
  display_csv.addItems();
}

main() {
  addItems();
  print(installation);
  installation.generate();
}
