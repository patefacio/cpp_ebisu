library installation;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'dart:io';
import 'package:id/id.dart';

String _getPath() {
  final script = Platform.script.toFilePath();
  return script.substring(0, script.indexOf('fcs/codegen')) + 'fcs';
}

final ebisuInstallation = () {
  useClangFormatter = true;
  return new Installation(new Id('ebisu'))
    ..logsApiInitializations = true
    ..rootFilePath = _getPath();
}();
