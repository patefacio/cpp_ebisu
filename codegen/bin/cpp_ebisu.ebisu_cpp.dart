import 'libs.dart' as libs;
import 'apps.dart' as apps;
import 'benchmarks.dart' as benchmarks;
import 'schemas.dart' as schemas;
import '../lib/ebisu_installation.dart';
import 'package:ebisu/ebisu.dart';
import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'package:ebisu_cpp/qt_support.dart';
import 'package:logging/logging.dart';

final _logger = new Logger('ebisu');

main() {
  Logger.root
    ..onRecord.listen((LogRecord r) =>
        print("${r.loggerName} [${r.level}]:\t${r.message}"))
    ..level = Level.SEVERE;

  defaultCppNamer = new QtNamer();
  generate() {
    ebisuInstallation
      ..doc = 'C++ library'
      ..installationBuilder = new CmakeInstallationBuilder.fromInstallation(ebisuInstallation)
      ..cppLoggers = [ /* TODO: cppLogger('ebisu'), cppLogger('goober')*/ ];

    addQtSupport(ebisuInstallation);

    ebisuInstallation.generate(generateBuildScripts: true,
          generateHeaderSmokeTest : false,
          generateDoxyFile : true,
          generateEmacs : true);
  }

  libs.addItems();

  apps.addItems();

  benchmarks.addBenchmarks();

  if(false) {
    schemas.addItems().then((var _) => generate());
  } else {
    generate();
  }

  print('''
**** NON GENERATED FILES ****
${indentBlock(brCompact(nonGeneratedFiles))}
''');

}
