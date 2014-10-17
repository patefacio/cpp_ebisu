library bin.date_time_converter;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final date_time_converter = app('date_time_converter')
  ..args = [
    arg('timestamp')
    ..descr = 'Some form of date or timestamp'
    ..isMultiple = true
    ..type = ArgType.STRING,
  ];

addItems() => installation.addApp(date_time_converter);

main() {
  addItems();
  installation.generate();
}