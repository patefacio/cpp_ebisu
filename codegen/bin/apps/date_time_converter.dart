library bin.date_time_converter;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final date_time_converter = app('date_time_converter')
  ..descr = '''
App for converting between various forms of date/time

Example:

> date_time_converter -t "2014-Oct-21 15:06:54.748639" -t 212280707214748639 -d 20010101 -d 2456952 -d 56951 -t 20010101T000000
|-----------------------------|------------------------|-----------------------------|-------------|---------|-----------|
| input                       | iso                    | timestamp                   | date        | julian  | modjulian |
|-----------------------------|------------------------|-----------------------------|-------------|---------|-----------|
| 20010101                    | 20010101T000000        | 2001-Jan-01 00:00:00        | 2001-Jan-01 | 2451911 | 51910     |
| 2456952                     | 20141021T000000        | 2014-Oct-21 00:00:00        | 2014-Oct-21 | 2456952 | 56951     |
| 56951                       | 20141021T000000        | 2014-Oct-21 00:00:00        | 2014-Oct-21 | 2456952 | 56951     |
| 2014-Oct-21 15:06:54.748639 | 20141021T150654.748639 | 2014-Oct-21 15:06:54.748639 | 2014-Oct-21 | 2456952 | 56951     |
| 212280707214748639          | 20141021T150654.748639 | 2014-Oct-21 15:06:54.748639 | 2014-Oct-21 | 2456952 | 56951     |
| 20010101T000000             | 20010101T000000        | 2001-Jan-01 00:00:00        | 2001-Jan-01 | 2451911 | 51910     |
'''
  ..customBlocks = [ fcbEndNamespace ]
  ..includes = [
    'fcs/timestamp/conversion.hpp',
    'fcs/utils/streamers/table/table.hpp',
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