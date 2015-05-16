library schemas;

import '../lib/ebisu_installation.dart';
import 'dart:async';
import 'schemas/code_metrics.dart' as code_metrics;

Future addItems() =>
  Future.wait([
    code_metrics.addItems()
  ]);

main() => addItems()
  .then((_) => ebisuInstallation.generate());

// end <library libs>
