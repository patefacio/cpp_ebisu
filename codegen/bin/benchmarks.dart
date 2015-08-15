library apps;

import '../lib/ebisu_installation.dart';
import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'benchmarks/make_exception.ebisu.dart' as make_exception;

addBenchmarks() {
  ebisuInstallation.benchmarks.add(make_exception.makeExceptionBenchmark);
}

main() {
  addBenchmarks();
  ebisuInstallation.generate();
}
