library schema.code_metrics;

import 'dart:async';
import 'package:ebisu_cpp/cpp.dart';
import 'package:ebisu_cpp/db_schema.dart';
import '../../lib/installation.dart';

Future main() =>
  readMysqlSchema('code_metrics')
  .then((Schema s) =>
      installation
      ..addSchemaCodeGenerator(new SchemaCodeGenerator(s))
      ..generate());
