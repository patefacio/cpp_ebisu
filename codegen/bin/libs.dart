import '../lib/installation.dart';
import 'libs/utils.dart' as utils;
import 'libs/raii.dart' as raii;

addItems() {
  utils.addItems();
  raii.addItems();
}

main() {
  addItems();
  print(installation);
  installation.generateItems();
}

// end <library libs>
