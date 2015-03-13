library bin.display_csv;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/fcs_installation.dart';

final display_csv = app('display_csv')
  ..namespace = namespace(['fcs'])
  ..requiredLibs = [
    'boost_date_time',
    'boost_regex',
  ];

addItems() => fcsInstallation.addApp(display_csv);

main() {
  addItems();
  fcsInstallation.generate();
}