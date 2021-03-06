library bin.date_time_converter;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final date_time_converter = app('date_time_converter')
  ..brief = 'App for converting between various forms of date/time.'
  ..descr = '''
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
  ..namespace = namespace(['ebisu'])
  ..customBlocks = [ fcbEndNamespace ]
  ..includes = [
    'ebisu/timestamp/conversion.hpp',
    'ebisu/utils/streamers/table.hpp',
    'ebisu/timestamp/conversion.hpp',
    'stdexcept',
  ]
  ..hasLogLevel = true
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

addItems() => ebisuInstallation.addApp(date_time_converter);

main() {
  addItems();
  ebisuInstallation.generate();
}