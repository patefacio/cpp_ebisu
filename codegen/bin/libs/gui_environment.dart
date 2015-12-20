library libs.gui_environment;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'package:ebisu_cpp/qt_support.dart';
import '../../lib/ebisu_installation.dart';

final environment = lib('environment')
  ..namespace = namespace([ 'ebisu', 'gui' ])
  ..headers = [
    header('environment')
    ..namespace = namespace(['ebisu', 'gui', 'environment'])
    ..classes = [
      qtClass('tree_path_model')
      ..bases = [base('QAbstractItemModel')]
      ..members = [
        member('column_headers')..type = 'Header_array_t',
        member('column_count')..type = 'size_t',
      ],
      qtClass('q_environment')
      ..bases = [base('QWidget')]
      ..members = [
        member('variable_list_table')..type = 'QTableWidget *',
        member('spitter')..type = 'QSplitter *',
        member('tree_path_model')..type = 'Tree_path_model *',
        member('path_splitter')..type = 'QSplitter *',
        member('problem_table')..type = 'QTableWidget *',
      ]
    ]
  ];

addItems() => ebisuInstallation.addLibs([ environment ]);

main() {
  addItems();
  ebisuInstallation.generate();
}