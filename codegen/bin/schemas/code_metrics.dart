library schema.code_metrics;

import 'dart:async';
import 'package:ebisu_cpp/db_schema.dart';
import 'package:magus/schema.dart';
import 'package:magus/odbc_ini.dart';
import 'package:magus/mysql.dart';
import '../../lib/installation.dart';


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

    return installation
      ..addSchemaCodeGenerator(
        new OtlSchemaCodeGenerator(s)
        ..queries = [ rusageQuery(s) ]
        ..tableFilter = (t) => !t.name.contains(new RegExp('multi|user')));
  });

Future main() =>
  addItems().then((_) => installation.generate());
