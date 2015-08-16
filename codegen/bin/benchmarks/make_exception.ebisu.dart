library bin.display_csv;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final _makeExceptionBenchmark = benchmark('make_exception')
  ..doc = 'Contrast the cost of *make_exception* usage with variety of throw styles'
  ..benchmarkHeader.classes.insert(0, exceptionClass('sample_exception'))
  ..benchmarkHeader.classes.insert(0, boostExceptionClass('boost_style_exception'))
  ..benchmarkHeader.includes.add('ebisu/utils/exception/make_exception.hpp')
  ..functions = [
    'make_exception_basic',
    'make_exception_with_function_name',
    'boost_throw',
    'no_throw',
  ];

addItems() => ebisuInstallation..benchmarks.add(_makeExceptionBenchmark);

main() {
  addItems();
  ebisuInstallation.generate();
}
