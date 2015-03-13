library schema.code_metrics;

import 'dart:async';
import 'package:ebisu_cpp_db/ebisu_cpp_db.dart';
import 'package:magus/schema.dart';
import 'package:magus/odbc_ini.dart';
import 'package:magus/mysql.dart';
import '../../lib/fcs_installation.dart';

rusageQuery(Schema s) {
  final cp = s._code_packages;
  final cl = s._code_locations;
  final rd = s._rusage_delta;

  final returns =
    [
      col(cp._name, 'package_name'),
      cl._label,
      cl._file_name,
      rd._created,
      cl._line_number,
      cl._git_commit
    ]..addAll(rd
        .columns
        .where((c) => !(cl.name == 'id' || cl.name == 'created')));

  return new Query(returns);

}

Future addItems() =>
  new MysqlEngine(OdbcIni.createConnectionPool('code_metrics'))
  .createSchemaReader()
  .readSchema('code_metrics')
  .then((Schema s) {

    final generator = new OtlSchemaCodeGenerator(fcsInstallation, s)
      ..installation = fcsInstallation
      ..queries = [ rusageQuery(s) ]
      ..tableFilter = (t) => !t.name.contains(new RegExp('multi|user'));

    return fcsInstallation..addLib(generator.lib);
  });

Future main() =>
  addItems().then((_) => fcsInstallation.generate());
