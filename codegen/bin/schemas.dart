import '../lib/installation.dart';
import 'schemas/code_metrics.dart' as code_metrics;

addItems() {
  code_metrics.addItems();
}

main() {
  addItems();
  installation.generate();
}

// end <library libs>
