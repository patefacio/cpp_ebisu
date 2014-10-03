library bin.display_csv;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final display_csv = app('display_csv');

addItems() => installation.addApp(display_csv);

main() {
  addItems();
  installation.generateItems();
}