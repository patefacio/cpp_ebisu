library bin.display_csv;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final makeExceptionBenchmark = benchmark('make_exception');

_addItems() => ebisuInstallation.benchmarks.add(makeExceptionBenchmark);

main() {
  _addItems();
  ebisuInstallation.generate();
}