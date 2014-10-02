library bin.raii;

import 'package:ebisu_cpp/cpp.dart';
import '../installation.dart';

final raii = lib('raii')
  ..namespace = namespace([ 'fcs', 'raii' ])
  ..headers = [
    header('change_tracker')
    ..classes = [
      class_('change_tracker')
      ..members = [
        member('saved_value')..type = 'T',
        member('target')..type = 'T',
      ],
      class_('change_tracker_next_value'),
    ],
    header('change_until_end_of_block')
    ..classes = [
      class_('change_until_end_of_block'),
    ]
  ];

addItems() => installation.addLib(raii);

main() {
  addItems();
  installation.generateItems();
}