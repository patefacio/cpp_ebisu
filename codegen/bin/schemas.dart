library schemas;

import '../lib/fcs_installation.dart';
import 'dart:async';
import 'schemas/code_metrics.dart' as code_metrics;

Future addItems() =>
  Future.wait([
    code_metrics.addItems()
  ]);

main() => addItems()
  .then((_) => fcsInstallation.generate());

// end <library libs>
