library schemas;

import 'dart:async';
import 'schemas/code_metrics.dart' as code_metrics;

Future main() => Future.wait([
  code_metrics.main()
]);

// end <library libs>
