library schema.code_metrics;

import 'dart:async';
import 'package:ebisu_cpp/cpp.dart';
import 'package:ebisu_cpp/db_schema.dart';
import 'package:magus/schema.dart';
import 'package:magus/odbc_ini.dart';
import 'package:magus/mysql.dart';
import '../../lib/installation.dart';

Future addItems() =>
  new MysqlEngine(OdbcIni.createConnectionPool('code_metrics'))
    .createSchemaReader()
    .readSchema('code_metrics')
    .then((Schema s) =>
        installation
        ..addSchemaCodeGenerator(
          new SchemaCodeGenerator(s)
          ..tableFilter = (t) => !t.name.contains(new RegExp('multi|user'))));

Future main() =>
  addItems().then((_) => installation.generate());
