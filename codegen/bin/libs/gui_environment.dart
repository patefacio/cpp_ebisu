library libs.gui_environment;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'package:ebisu_cpp/qt_support.dart';
import '../../lib/ebisu_installation.dart';

final guiEnvironment = lib('gui_environment')
  ..namespace = namespace(['ebisu', 'gui', 'environment'])
  ..impls = [
    impl('tree_path_model')..customBlocks = [fcbBeginNamespace]..includes.add('ebisu/gui/environment/q_environment.hpp'),
    impl('q_environment')..customBlocks = [fcbBeginNamespace]..includes.add('ebisu/gui/environment/q_environment.hpp'),
  ]
  ..headers = [
    header('q_environment')
    ..includes.addAll([
      'QHeaderView', 'vector',
      'QBoxLayout', 'QLabel',
      'ebisu/utils/streamers/vector.hpp', 'ebisu/timestamp/timestamp.hpp',
      'ebisu/environment/environment.hpp',
    ])
    ..classes = [
      class_('tree_data_item')
      ..defaultMemberAccess = ro
      ..customBlocks = [ clsPublic ]
      ..isStreamable = true
      ..usesStreamers = true
      ..usings = [
        usingPtr('tree_data_item', 'Tree_data_item'),
        usingSptr('tree_data_item', 'Tree_data_item'),
        using('tree_data_item_list', 'std::vector<Tree_data_item_sptr_t>'),
      ]
      ..memberCtors = [
        memberCtor(['data', 'row',
          memberCtorParm('parent')..defaultValue = 'nullptr',
          memberCtorParm('file_size')..defaultValue = 'std::string()',
          memberCtorParm('last_modified')..defaultValue = 'std::string()',])
      ]
      ..members = [
        member('data')..type = 'std::string',
        member('row')..init = 0,
        member('parent')..type = 'Tree_data_item_ptr_t',
        member('file_size')..type = 'std::string',
        member('last_modified')..type = 'std::string',
        member('children')..type = 'Tree_data_item_list_t'
      ],
      qtClass('tree_path_model')
      ..includes.add('array')
      ..usings = [
        using('header_array', 'std::array< char const*, 3>'),
        using('tree_data_item_sptr', 'Tree_data_item::Tree_data_item_sptr_t'),
        using('tree_data_item_ptr', 'Tree_data_item::Tree_data_item_ptr_t'),
      ]
      ..bases = [base('QAbstractItemModel')]
      ..members = [
        member('root')..type = 'Tree_data_item_sptr_t',
      ],
      qtClass('q_environment')
      ..bases = [base('QWidget')]
      ..members = [
        member('variable_list_table')..type = 'QTableWidget *',
        member('splitter')..type = 'QSplitter *',
        member('tree_path_model')..type = 'Tree_path_model *',
        member('tree_path_view')..type = 'QTreeView *',
        member('path_splitter')..type = 'QSplitter *',
        member('problem_table')..type = 'QTableWidget *',
      ]
    ]
  ];

addItems() => ebisuInstallation.addLibs([ guiEnvironment ]);

main() {
  addItems();
  ebisuInstallation.generate();
}