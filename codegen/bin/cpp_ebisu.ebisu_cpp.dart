import 'libs.dart' as libs;
import 'apps.dart' as apps;
import 'benchmarks.dart' as benchmarks;
import 'schemas.dart' as schemas;
import '../lib/ebisu_installation.dart';
import 'package:ebisu/ebisu.dart';
import 'package:ebisu_cpp/ebisu_cpp.dart';
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

  benchmarks.addBenchmarks();

  if(true) {
    schemas.addItems().then((var _) => generate());
  } else {
    generate();
  }

  print('''
**** NON GENERATED FILES ****
${indentBlock(brCompact(nonGeneratedFiles))}
''');

}
