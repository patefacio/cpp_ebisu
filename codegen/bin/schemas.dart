import 'dart:async';
import '../lib/installation.dart';
import 'schemas/code_metrics.dart' as code_metrics;

Future main() => Future.wait([
  code_metrics.main()
]);

// end <library libs>
