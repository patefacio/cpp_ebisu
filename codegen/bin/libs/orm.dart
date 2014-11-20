library bin.orm;

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
      'map',
      'set',
      'mutex',
      'boost/date_time/gregorian/gregorian.hpp',
      'boost/thread/tss.hpp',
    ]
    ..classes = [
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
      'fcs/utils/streamers/table.hpp',
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