library bin.utils;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final utils = lib('utils')
  ..namespace = namespace([ 'fcs', 'utils' ])
  ..headers = [
    header('block_indenter')
    ..includes = [
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
    header('fixed_size_char_array')
    ..includes = [ 'cstring', 'cassert', 'array', 'string' ]
    ..includeTest = true
    ..classes = [
      class_('fixed_size_char_array')
      ..template = [ 'int ARRAY_SIZE' ]
      ..usings = [ 'Array_t = std::array< char, ARRAY_SIZE >', ]
      ..customBlocks = [ clsPublic, clsPostDecl, clsPrivate ]
      ..members = [
        member('buffer_size')..type = 'int'
        ..isStatic=true..isConstExpr = true
        ..initText = 'ARRAY_SIZE'..cppAccess = public,
        member('last_index')..type = 'int'
        ..isStatic = true..isConstExpr = true
        ..initText = 'ARRAY_SIZE-1'..cppAccess = public,
        member('data')..type = 'Array_t',
      ],
    ],
    header('utils')
    ..includes = [ 'cmath', 'iostream', ]
    ..customBlocks = [ ]
    ..classes = [
      class_('value_min_max'),
      class_('version_control_commit'),
    ],
    header('version_control_commit')
    ..classes = [
      class_('version_control_commit')
      ..descr = '''
Provide static data with git commit for quickly identifying contents of build
with linux strings program'''
      ..isSingleton = true
      ..members = [
        member('git_commit')..type = 'char const* const',
        member('search_string')..type = 'char const* const',
      ]
    ],
    header('histogram')
    ..includes = [ 'fcs/utils/block_indenter.hpp',
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
        memberCtor([
          memberCtorParm('num_bins')..defaultValue = '20',
          memberCtorParm('cache_size')..defaultValue = '10' ]
                   )
      ],
      class_('histogram')
      ..usings = [ 'Result_vector_t = vector< T >' ]
      ..template = ['typename T = double' ]
      ..opOut
      ..members = [
        member('num_bins')..init = 20..access = ro..isConst = true,
        member('results')
        ..type = 'Result_vector_t'
        ..initText = 'Result_vector_t(num_bins_)'..access = ro,
      ]
      ..memberCtors = [
        memberCtor([
          memberCtorParm('num_bins')
          ..defaultValue = '20'

        ])..decls = ['IT begin', 'IT end']
        ..template = 'typename IT'
        ..customLabel = 'from_iterator',
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
    ..addLib(utils);

  final containers = lib('containers')
    ..namespace = _namespace
    ..headers = [
      header('containers')
      ..includes = [
        'fcs/utils/streamers/list.hpp',
        'fcs/utils/streamers/vector.hpp',
        'fcs/utils/streamers/deque.hpp',
        'fcs/utils/streamers/set.hpp',
        'fcs/utils/streamers/map.hpp',
      ],

      header('streamers')
      ..customBlocks = [ fcbBeginNamespace ]
      ..includes = [
        'memory',
        'iosfwd',
        'sstream',
      ],

      header('random')
      ..test.includes.addAll([
        'fcs/utils/streamers/containers.hpp',
        'fcs/timestamp/timestamp.hpp',
      ])
      ..includes = [
        'random',
        'limits',
        'cstdint',
        'fcs/orm/otl_utils.hpp',
        'fcs/utils/fixed_size_char_array.hpp',
        'fcs/timestamp/timestamp.hpp',
        'iostream', // TODO: remove
      ]
      ..classes = [
        class_('random_source')
        ..includeTest = true
        ..customBlocks = [ clsPublic, clsPostDecl ]
        ..members = [
          member('engine')..type = 'std::mt19937'..noInit = true
          ..cppAccess = public
        ]
      ],

      header('table')
      ..customBlocks = [fcbBeginNamespace]
      ..usings = [
        'String_list_t = std::vector< std::string >',
        'String_matrix_t = std::vector< String_list_t >',
        'Size_list_t = std::vector< size_t >',
      ]
      ..includes = [
        'fcs/utils/streamers/containers.hpp', 'boost/lexical_cast.hpp', 'boost/range.hpp',
        'vector', 'algorithm', 'iostream',
      ]
      ..classes = [
        class_('table_streamer')
        ..usings = [
          'Row_container_t = typename MatrixContainer::value_type',
        ]
        ..brief = 'Outputs data in tabular format - like output from database query'
        ..template = [
          'typename MatrixContainer = String_matrix_t',
          'typename T = typename MatrixContainer::value_type::value_type'
        ]
        ..customBlocks = [ clsPublic, clsPreDecl ]
        ..members = [
          member('matrix_container')
          ..refType = cref
          ..byRef = true
          ..brief = 'Matrix with data to stream'
          ..type = 'MatrixContainer',
          member('header')
          ..refType = cref
          ..byRef = true
          ..brief = 'List of headers for the columns'
          ..type = 'String_list_t',
        ]
        ..memberCtors = [
          memberCtor(['matrix_container', memberCtorParm('header')
            ..defaultValue = 'String_list_t()']
                     ),
        ]
      ]

    ];

  containers.headers.addAll(
    _containers.keys.map((c) =>
        header(c)
        ..includes = _containers[c]
        ..customBlocks = [fcbBeginNamespace]));

  installation.addLib(containers);
}

main() {
  addItems();
  installation.generate();
}