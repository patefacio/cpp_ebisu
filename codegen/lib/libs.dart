library fcs.libs;

import 'package:fcs/installation.dart';
// custom <additional imports>

import 'package:fcs/libs/utils.dart' as utils;
import 'package:fcs/libs/raii.dart' as raii;

// end <additional imports>

// custom <library libs>

addItems() {
  utils.addItems();
  raii.addItems();
}

main() {
  addItems();
  installation.generateItems();
}

// end <library libs>
