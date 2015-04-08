import 'libs.dart' as libs;
import 'apps.dart' as apps;
import 'schemas.dart' as schemas;
import '../lib/fcs_installation.dart';
import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'package:ebisu_cpp/hdf5_support.dart';
import 'package:logging/logging.dart';


main() {
  Logger.root
    ..onRecord.listen((LogRecord r) =>
        print("${r.loggerName} [${r.level}]:\t${r.message}"))
    ..level = Level.OFF;
  libs.addItems();
  apps.addItems();
  schemas.addItems()
    .then((var _) {
      fcsInstallation
        ..builders = [ cmakeInstallationBuilder() ]
        ..decorateWith(packetTableDecorator(
                [
                  logGroup('rusage_delta'),
                ]));

      fcsInstallation.generate();

      //print(fcsInstallation.progeny.map((c) => '  ${c.runtimeType}:${c.id}\n').toList());

      // installation
      //   .progeny
      //   .forEach((e) => print('=> ${e.runtimeType}:${e.id}:${e.entityPathIds.join(",")}'));
    });
}
