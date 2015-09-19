library libs.orm;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'package:ebisu_cpp/hdf5_support.dart';
import '../../lib/ebisu_installation.dart';

final h5_utils = lib('h5_utils')
  ..namespace = namespace([ 'ebisu', 'h5', 'utils' ])
  ..headers = [
    header('h5_random_access_store')
    ..customBlocks = [ fcbEndNamespace, ]
    ..enums = [
      enum_('store_open_type')
      ..values = [ 'open_create', 'open_read' ]
      ..isStreamable = true
    ]
    ..usings = [
    ]
    ..includes = [
      'memory',
      'string',
      'H5Cpp.h',
      'H5File.h',
      'H5PacketTable.h',
    ]
    ..classes = [
      class_('h5_random_access_store')
      ..doc = '''
Stores objects of type TYPE_STORED in an hdf5 data_set for basic random access
whose hdf5 data_set type (when used for creation) is specified by
H5_DATA_SET_SPECIFIER.
'''
      ..template = [
        'typename TYPE_STORED',
        'typename H5_DATA_SET_SPECIFIER = TYPE_STORED'
      ]
      ..usings = [
        usingSptr('packet_table', 'FL_PacketTable'),
        usingSptr('h5_file', 'H5::H5File'),
        using('h5_data_set_specifier', 'H5_DATA_SET_SPECIFIER'),
        using('group_id_list', 'std::vector<hid_t>'),
      ]
      ..memberCtors = [
        memberCtor([ 'file', 'open_type', 'group'])
        ..tag = 'create packet table'
        ..includesProtectBlock = true
      ]
      ..members = [
        member('file')..type = 'H5_file_sptr_t'..isByRef = true..isConst = true,
        member('open_type')..type = 'Store_open_type'..isConst = true,
        member('group')..type = 'std::string'..isConst = true,
        member('packet_table')..type = 'Packet_table_sptr_t',
      ]
      ..testScenarios = [

        testScenario('simple h5 data set random access',
            [ given('simple data set', []) ])
        ..preCodeBlock.snippets.add(addH5DataSetSpecifier(class_('sample')
            ..members = [
              member('age_in_years')..init = 0,
              member('height_in_inches')..init = 0.0,
            ]).definition
                                      )

      ]
    ],
  ];


addItems() => ebisuInstallation.addLibs([h5_utils]);

main() {
  addItems();
  ebisuInstallation.generate();
}