library bin.utils;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final utils = lib('utils')
  ..namespace = namespace([ 'fcs', 'utils' ])
  ..headers = [
    header('utils')
    ..headers = [ 'cmath', 'iostream' ]
    ..customBlocks = [ fcbPreNamespace, fcbPostNamespace, fcbBeginNamespace, fcbEndNamespace ]
    ..classes = [
      class_('block_indenter')..customBlocks = [ clsPreDecl, clsPublic, clsPostDecl ],
      class_('value_min_max'),
      class_('fixed_size_char_array'),
      class_('version_control_commit'),
      class_('histogram')
      ..assignCopy.useDefault = true
      ..assignMove.delete = true
      ..dtor.useDefault = true
      ..enums = [ enum_('foo')..values = ['red', 'green' ] ]
      ..customBlocks = [ clsProtected, clsPreDecl ]
      ..defaultCtor.hasCustom = true
      ..copyCtor.hasCustom = true
      ..opEqual
      ..opLess
      ..template = ['typename T = double', 'typename T2 = int']
      ..members = [
        member('num_bins')..init = 20..access = ro,
        member('results')
        ..type = 'Result_vector_t'..initText = 'Result_vector_t(num_bins_,999)'..access = ro,
        member('pi')..type = 'double'..access = rw..noInit = true,
        member('pid')..type = 'somenumtype'..initText = '(3.14**2.0)'
        ..refType = ref..byRef = true,
        member('goo')..byRef = true..access = rw..init = 'Fooberger',
        member('moo')..init = 'falal'..access = null,
        member('zoo')..init = 'falal'..cppAccess = protected,
      ],
    ]
  ];

final streamers_table = lib('table')
  ..namespace = namespace(['fcs','utils','streamers', 'table'])
  ..headers = [
    header('table')
    ..customBlocks = [fcbBeginNamespace]
    ..headers = [
      'fcs/utils/streamers/containers.hpp', 'boost/lexical_cast.hpp', 'boost/range.hpp',
      'vector', 'algorithm', 'iostream',
    ]
    ..classes = [
      class_('table_streamer')
      ..brief = 'Outputs data in tabular format - like output from database query'
      ..template = [
        'typename MatrixContainer',
        'typename T = typename MatrixContainer::value_type::value_type'
      ]
      ..opOut
      ..members = [
        member('matrix_container')
        ..refType = cref
        ..brief = 'Matrix with data to stream'
        ..type = 'MatrixContainer',
        member('header')
        ..refType = cref
        ..brief = 'List of headers for the columns'
        ..type = 'String_list_t',
      ]
      ..memberCtors = [
        memberCtor(['matrix_container', 'header'], { 'header' : 'String_list_t()' }),
      ]
    ]
  ];

final _namespace = namespace(['fcs','utils','streamers']);
final _core = 'fcs/utils/streamers/streamers.hpp';
final _containers = {
  'vector' : [ _core, 'iosfwd', 'vector' ],
  'set' : [ _core, 'iosfwd', 'set' ],
  'map' : [ _core, 'iosfwd', 'map' ],
  'list' : [ _core, 'iosfwd', 'list' ],
  'deque' : [ _core, 'iosfwd', 'deque' ],
  'ptr_map' : [ _core, 'boost/ptr_container/ptr_map.hpp', 'iosfwd' ],
  'ptr_set' : [ _core, 'boost/ptr_container/ptr_set.hpp', 'iosfwd' ],
  'ptr_vector' : [ _core, 'boost/ptr_container/ptr_vector.hpp', 'iosfwd' ],
};

addItems() {
  installation
  ..addLib(utils)
  ..addLib(streamers_table);

  _containers.forEach((c, headers) =>
      installation.addLib(lib(c)
          ..namespace = _namespace
          ..headers = [
            header(c)
            ..headers = headers
            ..customBlocks = [fcbBeginNamespace]
          ]));
}

main() {
  addItems();
  installation.generateItems();
}