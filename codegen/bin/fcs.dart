import 'libs.dart' as libs;
import 'apps.dart' as apps;
import 'schemas.dart' as schemas;


main() {
  libs.main();
  apps.main();
  schemas
    .main()
    .then((_) => print('Schema code generated!!!'));
}
