library schemas;

import '../lib/installation.dart';
import 'dart:async';
import 'schemas/code_metrics.dart' as code_metrics;


Future addItems() =>
  Future.wait([
    code_metrics.addItems()
  ]);

main() => addItems()
  .then((_) => installation.generate());

// end <library libs>
