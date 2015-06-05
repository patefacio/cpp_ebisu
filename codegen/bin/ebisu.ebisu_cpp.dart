import 'libs.dart' as libs;
import 'apps.dart' as apps;
import 'schemas.dart' as schemas;
import '../lib/ebisu_installation.dart';
import 'package:ebisu/ebisu.dart';
import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'package:ebisu_cpp/hdf5_support.dart';
import 'package:logging/logging.dart';

final _logger = new Logger('ebisu');

main() {
  Logger.root
    ..onRecord.listen((LogRecord r) =>
        print("${r.loggerName} [${r.level}]:\t${r.message}"))
    ..level = Level.SEVERE;

  generate() {
    ebisuInstallation
      ..doc = 'C++ library'
      ..cppLoggers = [ /* TODO: cppLogger('ebisu'), cppLogger('goober')*/ ]
      ..generate(generateBuildScripts: true,
          generateHeaderSmokeTest : false,
          generateDoxyFile : true,
          generateEmacs : true);
  }

  libs.addItems();

  apps.addItems();

  if(true) {
    schemas.addItems()
      .then((var _) {
        ebisuInstallation
          ..decorateWith(packetTableDecorator(
                  [
                    logGroup('rusage_delta'),
                  ]));

        generate();

        ebisuInstallation.progeny
          .where((p) => p is Header)
          .forEach((l) => print(l.filePath));

          //ebisuInstallation.progeny.forEach((p) => print(p.detailedPath));
      });
  } else {
    generate();
  }

}
