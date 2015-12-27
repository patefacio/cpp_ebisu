library libs.gui_environment;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'package:ebisu_cpp/qt_support.dart';
import '../../lib/ebisu_installation.dart';

final environment = lib('environment')
  ..namespace = namespace([ 'ebisu', 'gui' ])
  ..headers = [
    header('environment')
    ..includes.add('QtWidgets/QHeaderView')
    ..namespace = namespace(['ebisu', 'gui', 'environment'])
    ..classes = [
      qtClass('tree_path_model')
      ..includes.add('array')
      ..usings = [ using('header_array', 'std::array< char*, 3>') ]
      ..bases = [base('QAbstractItemModel')]
      ..members = [
        member('column_headers')..type = 'Header_array_t'..isStatic = true..access = ro,
        member('column_count')..type = 'size_t'..isStatic = true..access = ro,
      ],
      qtClass('q_environment')
      ..bases = [base('QWidget')]
      ..members = [
        member('variable_list_table')..type = 'QTableWidget *',
        member('slpitter')..type = 'QSplitter *',
        member('tree_path_model')..type = 'Tree_path_model *',
        member('tree_path_view')..type = 'QTreeView *',
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