library schema.code_metrics;

import 'package:ebisu_cpp/cpp.dart';
import 'package:ebisu_cpp/db_schema.dart';
import '../../lib/installation.dart';

final code_metrics =
  new SchemaCodeGenerator(new Schema([]));

addItems() =>
  installation
  ..addSchemaCodeGenerator(code_metrics);

main() {
  addItems();
  installation.generateItems();
}