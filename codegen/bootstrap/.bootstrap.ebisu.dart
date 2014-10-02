import "dart:io";
import "package:path/path.dart" as path;
import "package:ebisu/ebisu_dart_meta.dart";
import "package:logging/logging.dart";

String _topDir;

void main() {
  Logger.root.onRecord.listen((LogRecord r) =>
      print("${r.loggerName} [${r.level}]:\t${r.message}"));
  String here = path.dirname(path.dirname(path.absolute(Platform.script.path)));
  print(here);
  final imports = [ 'package:ebisu_cpp/cpp.dart' ];
  System ebisu = system('fcs')
    ..pubSpec.addDependency(new PubDependency('ebisu'))
    ..pubSpec.addDependency(new PubDependency('ebisu_cpp'))
    ..pubSpec.addDependency(new PubDependency('path'))
    ..rootPath = here;
  ebisu.generate();
}
