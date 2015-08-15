library installation;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'dart:io';
import 'package:id/id.dart';

String _getPath() {
  final script = Platform.script.toFilePath();
  return script.substring(0, script.indexOf('cpp_ebisu/codegen')) + 'cpp_ebisu';
}

final ebisuInstallation = () {
  useClangFormatter = true;
  return new Installation(new Id('ebisu'))
    ..rootFilePath = _getPath();
}();
