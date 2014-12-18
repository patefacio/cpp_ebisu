library installation;

import 'package:ebisu_cpp/cpp.dart';
import 'dart:io';
import 'package:id/id.dart';

String _getPath() {
  final script = Platform.script.path;
  return script.substring(0, script.indexOf('fcs/codegen')) + 'fcs';
}

final installation = () {
  useClangFormatter = true;
  return new Installation(new Id('fcs'))
    ..root = _getPath();
}();
