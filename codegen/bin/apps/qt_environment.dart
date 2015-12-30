library bin.display_csv;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'package:ebisu_cpp/qt_support.dart';
import '../../lib/ebisu_installation.dart';

final environment = qtApp('environment')
  ..namespace = namespace(['ebisu', 'gui'])
  ..customBlocks = [ fcbEndNamespace ]
  ..includes = [
    'ebisu/environment/environment.hpp',
    'ebisu/gui/environment/q_environment.hpp',
    'QApplication',
    'QPushButton',
  ];

addItems() => ebisuInstallation.addApp(environment);

main() {
  addItems();
  ebisuInstallation.generate();
}