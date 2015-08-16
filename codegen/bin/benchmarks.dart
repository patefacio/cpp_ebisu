library apps;

import '../lib/ebisu_installation.dart';
import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'benchmarks/make_exception.ebisu.dart' as make_exception;

addBenchmarks() {
  make_exception.addItems();
}

main() {
  addBenchmarks();
  ebisuInstallation.generate();
}
