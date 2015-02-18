library bin.display_csv;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/installation.dart';

final display_csv = app('display_csv')
  ..namespace = namespace(['fcs'])
  ..requiredLibs = [
    'boost_date_time',
    'boost_regex',
  ];

addItems() => installation.addApp(display_csv);

main() {
  addItems();
  installation.generate();
}