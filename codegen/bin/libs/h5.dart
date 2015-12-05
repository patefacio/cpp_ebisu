library libs.orm;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import 'package:ebisu_cpp/hdf5_support.dart';
import '../../lib/ebisu_installation.dart';

final h5_utils = lib('h5_utils')
  ..requiresLogging = true
  ..namespace = namespace(['ebisu', 'h5', 'utils'])
  ..headers = [
    header('h5_random_access_store')
      ..customBlocks = [fcbEndNamespace,]
      ..enums = [
        enum_('store_open_type')
          ..doc = '''
H5_random_access_store may create a packet table or be created from an
existing packet table.'''
          ..values = ['open_create', 'open_read']
          ..isStreamable = true
      ]
      ..usings = []
      ..includes = [
        'array',
        'memory',
        'string',
        'exception',
        'H5Cpp.h',
        'H5File.h',
        'H5PacketTable.h',
        'boost/filesystem/path.hpp',
        'ebisu/utils/streamers/array.hpp',
      ]
      ..classes = [
        class_('h5_random_access_store')
          ..doc = '''
Stores objects of with schema specified by DSS - a dataset sepcifier.
DSS must define type *typename DSS::Record_t* which is the type of the
instances being stored/read from the recordset.
'''
          ..template = ['typename DSS',]
          ..customBlocks = [clsPrivate, clsPublic]
          ..usings = [
            usingSptr('h5_file', 'H5::H5File'),
            using('h5_data_set_specifier', 'DSS'),
            using('record', 'typename DSS::Record_t'),
            using('group_id_list', 'std::vector<hid_t>'),
            usingUptr('packet_table', 'FL_PacketTable'),
          ]
          ..memberCtors = [
            memberCtor(['file', 'open_type', 'group'])
              ..tag = 'create packet table'
              ..includesProtectBlock = true
          ]
          ..members = [
            member('file')
              ..doc =
                  'Pointer to file containing (or to contain) data set for random access'
              ..type = 'H5_file_sptr_t'
              ..isByRef = true
              ..isConst = true
              ..hasNoInit = true,
            member('open_type')
              ..doc =
                  'Determines if packet table will be created [open_create] or read [open_read]'
              ..type = 'Store_open_type'
              ..isConst = true
              ..hasNoInit = true,
            member('group')
              ..doc = 'The group indicating where to find the data set'
              ..type = 'std::string'
              ..hasNoInit = true,
            member('packet_table')
              ..doc = 'Pointer to the packet table'
              ..type = 'Packet_table_uptr_t',
          ]
          ..testScenarios = [
            () {
              final sample = class_('sample')
                ..defaultCtor.usesDefault = true
                ..isImmutable = true
                ..isStreamable = true
                ..usesStreamers = true
                ..usings = [
                  using('char_10_bytes_t', 'std::array<char, 10>'),
                  using('unrecognizable', 'int'),
                  using('buffer', 'std::array< char, 16 >'),
                ]
                ..members = [
                  member('m_char')
                  ..type = 'char'
                  ..init = 0,
                  member('m_unsigned_char')
                  ..type = 'unsigned char'
                  ..init = 0,
                  member('m_signed_char')
                  ..type = 'signed char'
                  ..init = 0,
                  member('m_short')
                  ..type = 'short'
                  ..init = 0,
                  member('m_int')
                  ..type = 'int'
                  ..init = 0,
                  member('m_long')
                  ..type = 'long'
                  ..init = 0,
                  member('m_long_long')
                  ..type = 'long long'
                  ..init = 0,
                  member('bogus')
                  ..doc = 'Should be ignored for hdf5'
                  ..type = 'Buffer_t',
                  member('m_unsigned_int')
                  ..type = 'unsigned int'
                  ..init = 0,
                  member('m_unsigned_long')
                  ..type = 'unsigned long'
                  ..init = 0,
                  member('m_unsigned_long_long')
                  ..type = 'unsigned long long'
                  ..init = 0,
                  member('m_double')
                  ..type = 'double'
                  ..init = 0,
                  member('m_long_double')
                  ..type = 'long double'
                  ..init = 0,
                  member('m_sentinal')
                  ..type = 'char'
                  ..init = 0,
                  member('m_str_10_bytes')
                  ..type = 'Char_10_bytes_t'
                  ..isByRef = true,
                ];

              mapper(String cppType) => cppType == 'Char_10_bytes_t'
                ? new PacketMemberString(10)
                : cppTypeToHdf5Type(cppType);

              final dss = createH5DataSetSpecifier(sample, mapper);
              final sampleScenario =
                  testScenario('simple h5 data set random access');
              sampleScenario
                ..preCodeBlock.snippets.add('''
namespace scoped {
${sample.definition}

${dss.definition}
}
''')
                ..withGiven('simple data set', (Given given) {
                });
              return sampleScenario;
            }()
          ]
      ],
  ];

addItems() => ebisuInstallation.addLibs([h5_utils]);

main() {
  addItems();
  ebisuInstallation.generate();
}
