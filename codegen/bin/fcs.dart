import 'libs.dart' as libs;
import 'apps.dart' as apps;
import 'schemas.dart' as schemas;
import '../lib/installation.dart';
import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'package:logging/logging.dart';


main() {
  Logger.root
    ..onRecord.listen((LogRecord r) =>
        print("${r.loggerName} [${r.level}]:\t${r.message}"))
    ..level = Level.WARNING;
  libs.addItems();
  apps.addItems();
  schemas.addItems()
    .then((var _) {
      installation
        ..builders = [ cmakeInstallationBuilder() ]
        ..generate();
      print('Installed libs ${installation.generatedLibs.map((l) => l.id)}');
      print('Installed apps ${installation.generatedApps.map((l) => l.id)}');
    });
}
