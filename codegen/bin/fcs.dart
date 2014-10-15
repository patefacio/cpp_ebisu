import 'libs.dart' as libs;
import 'apps.dart' as apps;
import 'schemas.dart' as schemas;
import 'package:ebisu_cpp/cpp.dart';

main() {
  libs.main();
  apps.main();
  schemas
    .main()
    .then((_) => print('Schema code generated!!!'));
}
