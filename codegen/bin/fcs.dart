import 'libs.dart' as libs;
import 'apps.dart' as apps;
import 'schemas.dart' as schemas;
import '../lib/fcs_installation.dart';
import 'package:ebisu/ebisu.dart';
import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'package:ebisu_cpp/hdf5_support.dart';
import 'package:logging/logging.dart';

final _logger = new Logger('fcs');

main() {
  Logger.root
    ..onRecord.listen((LogRecord r) =>
        print("${r.loggerName} [${r.level}]:\t${r.message}"))
    ..level = Level.SEVERE;

  generate() {
    fcsInstallation
      ..doc = 'C++ library'
      ..cppLoggers = [ /* TODO: cppLogger('fcs'), cppLogger('goober')*/ ]
      ..generate(generateBuildScripts: true, generateHeaderSmokeTest : false, generateDoxyFile : true);
  }

  libs.addItems();

  apps.addItems();

  if(true) {
    schemas.addItems()
      .then((var _) {
        fcsInstallation
          ..decorateWith(packetTableDecorator(
                  [
                    logGroup('rusage_delta'),
                  ]));

        generate();
      });
  } else {
    generate();
  }
}
