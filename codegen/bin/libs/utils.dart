library bin.utils;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final utils = lib('utils')
  ..namespace = namespace([ 'fcs', 'utils' ])
  ..headers = [
    header('block_indenter')
    ..headers = [
      'boost/thread/tss.hpp'
    ]
    ..classes = [
      class_('block_current_indent')
      ..isSingleton = true
      ..customBlocks = [ clsPublic, clsPrivate ]
      ..members = [
        member('indentation_length')
        ..type = 'boost::thread_specific_ptr< int >'
      ],
      class_('block_indenter')
      ..customBlocks = [ clsPublic ]
    ],
    header('utils')
    ..headers = [ 'cmath', 'iostream' ]
    ..customBlocks = [ ]
    ..classes = [
      class_('value_min_max'),
      class_('fixed_size_char_array'),
      class_('version_control_commit'),
    ],
    header('histogram')
    ..headers = [ 'fcs/utils/block_indenter.hpp',
      'fcs/utils/streamers/containers.hpp',
      'boost/accumulators/accumulators.hpp',
      'boost/accumulators/statistics/density.hpp',
      'boost/algorithm/minmax_element.hpp',
      'iostream',
      'vector'
    ]
    ..classes = [
      class_('histogram_statistical')
      ..template = ['typename T = double' ]
      ..customBlocks = [ clsPublic ]
      ..usings = [
        '''
Accumulator_t = boost::accumulators::accumulator_set<
  T,
  boost::accumulators::features< boost::accumulators::tag::density >
>''',
        '''
Hist_results_t = boost::iterator_range<
  typename std::vector< std::pair< T, T > >::iterator
>''',
      ]
      ..members = [
        member('num_bins')..access = ro..type = 'int'..noInit = true..isConst = true,
        member('cache_size')..access = ro..type = 'int'..noInit = true..isConst = true,
        member('accumulator')..type = 'Accumulator_t'..access = ro
        ..initText = '''

  boost::accumulators::tag::density::num_bins = num_bins_,
  boost::accumulators::tag::density::cache_size = cache_size_''',
      ]
      ..memberCtors = [
        memberCtor([ 'num_bins', 'cache_size' ], { 'num_bins': '20', 'cache_size' : '10' })
      ],
      class_('histogram')
      ..usings = [ 'Result_vector_t = vector< T >' ]
      ..template = ['typename T = double' ]
      ..opOut
      ..members = [
        member('num_bins')..init = 20..access = ro..isConst = true,
        member('results')..type = 'Result_vector_t'..initText = 'Result_vector_t(num_bins_)'..access = ro,
      ]
      ..memberCtors = [
        memberCtor([ 'num_bins' ], { 'num_bins' : 20 }, ['IT begin', 'IT end'])
        ..template = 'typename IT'
        ..hasCustom = true,
      ]
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
      ..customBlocks = [ clsPublic ]
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
  installation.generate();
}