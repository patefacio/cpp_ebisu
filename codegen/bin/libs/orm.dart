library bin.raii;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final orm = lib('orm')
  ..namespace = namespace([ 'fcs', 'orm' ])
  ..headers = [
    header('orm')
    ..isApiHeader = true
    ..customBlocks = [ fcbCustomIncludes, fcbPostNamespace ]
    ..includes = [
      'vector',
      'set',
      'mutex',
      'boost/date_time/gregorian/gregorian.hpp',
    ]
    ..classes = [
      class_('connection_info')
      ..customBlocks = [ clsPublic ]
      ..memberCtors = [ memberCtor(['user_id', 'password', 'dsn']) ]
      ..members = [
        member('user_id')..type = 'std::string'..access = ro,
        member('password')..type = 'std::string'..access = ro,
        member('dsn')..type = 'std::string'..access = ro,
      ],
      class_('connection_registry')
      ..template = [
        'typename LOCK_TYPE = std::mutex',
        'typename GUARD_TYPE = std::lock_guard< LOCK_TYPE >',
      ]
      ..usings = [
        'Lock_t = LOCK_TYPE',
        'Guard_t = GUARD_TYPE',
        'Connection_info_map_t = std::map< std::string, Connection_info >',
        'Thread_connection_ptr = boost::thread_specific_ptr< otl_connect >',
        'Thread_connection_map_t = std::map< std::string, Thread_connection_ptr >',
      ]
      ..customBlocks = [ clsPublic ]
      ..isSingleton = true
      ..members = [
        member('connection_info_map')..type = 'Connection_info_map_t',
        member('lock')..type = 'Lock_t',
        member('thread_connection_map')..type = 'Thread_connection_map_t',
      ],
      class_('otl_log_level')
      ..customBlocks = [ clsPublic, clsPostDecl ]
      ..members = [ member('level')..type = 'int'
        ..noInit = true..isStatic = true ]
      ..template = [ 'int OTL_LOG_LEVEL = 0' ],
    ]
    ..usings = [
      'String_list_t = std::vector< std::string >',
      'String_table_t = std::vector< String_list_t >',
      'Date_t = boost::gregorian::date',
      'Date_set_t = std::set< Date_t >',
    ],
    header('orm_to_string_table')
    ..descr = 'Functions to turn recordset lists into string lists'
    ..customBlocks = [ fcbEndNamespace, ]
    ..usings = [
    ]
    ..includes = [
      'string',
      'fcs/utils/streamers/table/table.hpp',
    ],
    header('otl_utils')
    ..customBlocks = [ fcbPreNamespace, fcbEndNamespace, fcbPostNamespace ]
    ..includes = [
      "fcs/utils/fixed_size_char_array.hpp",
      "boost/date_time/gregorian/formatters.hpp",
      "boost/date_time/gregorian/gregorian_types.hpp",
      "boost/date_time/posix_time/posix_time.hpp",
      "boost/algorithm/string/replace.hpp",
      "string",
    ],
  ];


addItems() => installation.addLibs([orm]);

main() {
  addItems();
  installation.generate();
}