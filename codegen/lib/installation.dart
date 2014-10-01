library fcs.installation;

import 'package:ebisu_cpp/cpp.dart';
// custom <additional imports>

import 'dart:io';
import 'package:id/id.dart';
import 'package:path/path.dart';
import 'package:fcs/libs.dart' as libs;

// end <additional imports>

// custom <library installation>

String _getPath() {
  final script = Platform.script.path;
  return script.substring(0, script.indexOf('fcs/codegen')) + 'fcs';
}

final installation = new Installation(new Id('fcs'))
  ..root = _getPath();

main() {
  libs.addItems();
  installation.generateItems();
}


// end <library installation>
