library bin.raii;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final orm = lib('orm')
  ..namespace = namespace([ 'fcs', 'orm' ])
  ..headers = [
    header('orm')
    ..isApiHeader = true
    ..includes = [ 'vector' ]
    ..usings = [
      'String_list_t = std::vector< std::string >',
      'String_table_t = std::vector< String_list_t >',
    ],
    header('otl_config')
    ..descr = 'Defines to be pulled in before otl'
    ..customBlocks = [ fcbPostNamespace ]
    ..classes = [
      class_('otl_log_level')
      ..customBlocks = [ clsPublic, clsPostDecl ]
      ..members = [ member('level')..type = 'int'
        ..noInit = true..isStatic = true ]
      ..template = [ 'int OTL_LOG_LEVEL = 0' ]
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
      'fcs/orm/otl_config.hpp',
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