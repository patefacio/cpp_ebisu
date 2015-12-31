library libs;

import '../lib/ebisu_installation.dart';
import 'libs/utils.dart' as utils;
import 'libs/raii.dart' as raii;
import 'libs/orm.dart' as orm;
import 'libs/timestamp.dart' as timestamp;
import 'libs/linux_specific.dart' as linux_specific;
import 'libs/performance.dart' as performance;
import 'libs/h5.dart' as h5;
import 'libs/mongo.dart' as mongo;
import 'libs/logger.dart' as logger;
import 'libs/environment.dart' as environment;
import 'libs/gui_environment.dart' as gui_environment;


addItems() {
  linux_specific.addItems();
  utils.addItems();
  raii.addItems();
  orm.addItems();
  timestamp.addItems();
  performance.addItems();
  h5.addItems();
  mongo.addItems();
  logger.addItems();
  environment.addItems();
  gui_environment.addItems();
}

main() {
  addItems();
  ebisuInstallation.generate();
}
