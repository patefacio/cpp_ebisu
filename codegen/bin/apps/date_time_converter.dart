library bin.date_time_converter;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final date_time_converter = app('date_time_converter')
  ..descr = '''
App for converting between various forms of date/time

Example:

> date_time_converter -t '2014-Oct-21 15:06:54.748639' -t 212280707214748639 -d 20010101 -d 2456952 -d 56951 -t 20010101T000000
|-----------------------------|--------------------|------------|------------------------|-----------------------------|-------------|---------|------------|
| input                       | ticks              | time_t     | iso                    | timestamp                   | date        | julian  | modjulian  |
|-----------------------------|--------------------|------------|------------------------|-----------------------------|-------------|---------|------------|
| min_date_time               | 192879360000000000 | -807574016 | 14000101T000000        | 1400-Jan-01 00:00:00        | 1400-Jan-01 | 2232400 | 4294799695 |
| min_date_time               | 464269103999999999 | -769665    | 99991231T235959.999999 | 9999-Dec-31 23:59:59.999999 | 9999-Dec-31 | 5373484 | 2973483    |
| now                         | 212285674057364146 | 1418870857 | 20141218T024737.364146 | 2014-Dec-18 02:47:37.364146 | 2014-Dec-18 | 2457010 | 57009      |
| 20010101                    | 211845110400000000 | 978307200  | 20010101T000000        | 2001-Jan-01 00:00:00        | 2001-Jan-01 | 2451911 | 51910      |
| 2456952                     | 212280652800000000 | 1413849600 | 20141021T000000        | 2014-Oct-21 00:00:00        | 2014-Oct-21 | 2456952 | 56951      |
| 56951                       | 212280652800000000 | 1413849600 | 20141021T000000        | 2014-Oct-21 00:00:00        | 2014-Oct-21 | 2456952 | 56951      |
| 2014-Oct-21 15:06:54.748639 | 212280707214748639 | 1413904014 | 20141021T150654.748639 | 2014-Oct-21 15:06:54.748639 | 2014-Oct-21 | 2456952 | 56951      |
| 212280707214748639          | 212280707214748639 | 1413904014 | 20141021T150654.748639 | 2014-Oct-21 15:06:54.748639 | 2014-Oct-21 | 2456952 | 56951      |
| 20010101T000000             | 211845110400000000 | 978307200  | 20010101T000000        | 2001-Jan-01 00:00:00        | 2001-Jan-01 | 2451911 | 51910      |
'''
//   ..descr = '''
// All queries are (select
//   code_packages.name as package_name,
//   code_locations.label,
//   code_locations.file_name,
//   rusage_delta.created,
//   code_locations.line_number,
//   code_locations.git_commit,
//   rusage_delta.id,
//   rusage_delta.code_locations_id,
//   rusage_delta.created,
//   rusage_delta.start_processor,
//   rusage_delta.end_processor,
//   rusage_delta.cpu_mhz,
//   rusage_delta.debug,
//   rusage_delta.user_time_sec,
//   rusage_delta.user_time_usec,
//   rusage_delta.system_time_sec,
//   rusage_delta.system_time_usec,
//   rusage_delta.ru_maxrss,
//   rusage_delta.ru_ixrss,
//   rusage_delta.ru_idrss,
//   rusage_delta.ru_isrss,
//   rusage_delta.ru_minflt,
//   rusage_delta.ru_majflt,
//   rusage_delta.ru_nswap,
//   rusage_delta.ru_inblock,
//   rusage_delta.ru_oublock,
//   rusage_delta.ru_msgsnd,
//   rusage_delta.ru_msgrcv,
//   rusage_delta.ru_nsignals,
//   rusage_delta.ru_nvcsw,
//   rusage_delta.ru_nivcsw
// from
//   rusage_delta
//   inner join code_locations on rusage_delta.code_locations_id = code_locations.id
//   inner join code_packages on code_locations.code_packages_id = code_packages.id
// '''
  ..customBlocks = [ fcbEndNamespace ]
  ..includes = [
    'fcs/timestamp/conversion.hpp',
    'fcs/utils/streamers/table.hpp',
    'fcs/timestamp/conversion.hpp',
    'stdexcept',
  ]
  ..requiredLibs = [
    'boost_program_options',
    'boost_date_time',
    'boost_regex',
  ]
  ..args = [
    arg('timestamp')
    ..shortName = 't'
    ..descr = 'Some form of timestamp'
    ..isMultiple = true
    ..type = ArgType.STRING,
    arg('date')
    ..shortName = 'd'
    ..descr = 'Some form of date'
    ..isMultiple = true
    ..type = ArgType.STRING,
  ];

addItems() => installation.addApp(date_time_converter);

main() {
  addItems();
  installation.generate();
}