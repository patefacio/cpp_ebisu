library libs.utils;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final utils = lib('utils')
  ..namespace = namespace([ 'ebisu', 'utils' ])
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
    ..testScenarios = [

      testScenario('sizeof matches array size',
          given('fixed_size_char_array of size six', [],
              then('sizeof is a match'))),

      testScenario('array size initialized with smaller cstr',
          given('array size six inited with cstr size three', [],
              then('result has two chars and null'))),

      testScenario('array size initialized with larger cstr',
          given('array size three inited with cstr size six', [],
              then('result has two chars and null'))),

      testScenario('index operator works',
          given('array initialized with six chars', [],
              then('all chars are accessible'))),

      testScenario('equality operator works',
          given('array initted with string', [],
              [
                then('equals that string'),
                then('does not equal another string'),
                then('str accessor works')
              ])),

    ]
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
      ]
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
    ..includes = [ 'ebisu/utils/block_indenter.hpp',
      'ebisu/utils/streamers/containers.hpp',
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
        member('num_bins')..access = ro..type = 'int'..hasNoInit = true..isConst = true,
        member('cache_size')..access = ro..type = 'int'..hasNoInit = true..isConst = true,
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
        ..isExplicit = true
        ..template = 'typename IT'
        ..customLabel = 'from_iterator',
      ]
    ]

  ];

final exception = lib('exception')
  ..namespace = namespace(['ebisu', 'utils', 'exception'])
  ..headers = [
    header('make_exception')
    ..includes = [
      'boost/exception/all.hpp',
      'exception',
    ]
    ..customBlocks = [fcbBeginNamespace]
  ];

final _namespace = namespace(['ebisu','utils','streamers']);
final _core = 'ebisu/utils/streamers/streamers.hpp';
final _containers = {
  'vector' : [ _core, 'iosfwd', 'vector' ],
  'set' : [ _core, 'iosfwd', 'set' ],
  'map' : [ _core, 'iosfwd', 'map' ],
  'list' : [ _core, 'iosfwd', 'list' ],
  'array': [ _core, 'iosfwd', 'array' ],
  'deque' : [ _core, 'iosfwd', 'deque' ],
  'ptr_map' : [ _core, 'boost/ptr_container/ptr_map.hpp', 'iosfwd' ],
  'ptr_set' : [ _core, 'boost/ptr_container/ptr_set.hpp', 'iosfwd' ],
  'ptr_vector' : [ _core, 'boost/ptr_container/ptr_vector.hpp', 'iosfwd' ],
};

addItems() {
  ebisuInstallation
    ..addLibs([utils, exception]);

  final containers = lib('streamers')
    ..namespace = _namespace
    ..headers = [
      header('containers')
      ..includes = [
        'ebisu/utils/streamers/list.hpp',
        'ebisu/utils/streamers/vector.hpp',
        'ebisu/utils/streamers/deque.hpp',
        'ebisu/utils/streamers/set.hpp',
        'ebisu/utils/streamers/map.hpp',
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
        'ebisu/utils/streamers/containers.hpp',
        'ebisu/timestamp/timestamp.hpp',
      ])
      ..includes = [
        'random',
        'limits',
        'cstdint',
        'ebisu/orm/otl_utils.hpp',
        'ebisu/utils/fixed_size_char_array.hpp',
        'ebisu/timestamp/timestamp.hpp',
        'iostream', // TODO: remove
      ]
      ..classes = [
        class_('random_source')
        ..customBlocks = [ clsPublic, clsPostDecl ]
        ..members = [
          member('engine')..type = 'std::mt19937'..hasNoInit = true
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
        'ebisu/utils/streamers/containers.hpp', 'boost/lexical_cast.hpp', 'boost/range.hpp',
        'vector', 'algorithm', 'iostream',
      ]
      ..classes = [
        class_('table_streamer')
        ..template = [
          'typename MatrixContainer = String_matrix_t',
        ]
        ..usings = [
          using('matrix_container', 'MATRIX_CONTAINER'),
          using('row_container', 'typename Matrix_container_t::value_type'),
        ]
        ..brief = 'Outputs data in tabular format - like output from database query'
        ..customBlocks = [ clsPublic, clsPreDecl ]
        ..members = [
          member('matrix_container')
          ..refType = cref
          ..isByRef = true
          ..brief = 'Matrix with data to stream'
          ..type = 'Matrix_container_t',
          member('header')
          ..refType = cref
          ..isByRef = true
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

  ebisuInstallation.addLib(containers);
}

main() {
  addItems();
  ebisuInstallation.generate();
}