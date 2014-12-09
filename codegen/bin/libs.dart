library libs;

import '../lib/installation.dart';
import 'libs/utils.dart' as utils;
import 'libs/raii.dart' as raii;
import 'libs/orm.dart' as orm;
import 'libs/timestamp.dart' as timestamp;

addItems() {
  utils.addItems();
  raii.addItems();
  orm.addItems();
  timestamp.addItems();
}

main() {
  addItems();
  print(installation);
  installation.generate();
}

// end <library libs>
