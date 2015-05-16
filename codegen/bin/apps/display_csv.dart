library bin.display_csv;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final display_csv = app('display_csv')
  ..namespace = namespace(['ebisu'])
  ..requiredLibs = [
    'boost_date_time',
    'boost_regex',
  ];

addItems() => ebisuInstallation.addApp(display_csv);

main() {
  addItems();
  ebisuInstallation.generate();
}