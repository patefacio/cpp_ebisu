library libs;

import '../lib/ebisu_installation.dart';
import 'libs/utils.dart' as utils;
import 'libs/raii.dart' as raii;
import 'libs/orm.dart' as orm;
import 'libs/timestamp.dart' as timestamp;
import 'libs/linux_specific.dart' as linux_specific;
import 'libs/performance.dart' as performance;


addItems() {
  linux_specific.addItems();
  utils.addItems();
  raii.addItems();
  orm.addItems();
  timestamp.addItems();
  performance.addItems();
}

main() {
  addItems();
  ebisuInstallation.generate();
}

// end <library libs>
