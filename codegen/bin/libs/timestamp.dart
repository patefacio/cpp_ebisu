library bin.raii;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final timestamp = lib('timestamp')
  ..namespace = namespace([ 'fcs', 'timestamp' ])
  ..headers = [
    header('timestamp')
    ..customBlocks = [ fcbEndNamespace ]
    ..usings = [
      'Timestamp_t = boost::posix_time::ptime',
      'Time_duration_t = boost::posix_time::time_duration',
      'Date_t = boost::gregorian::date',
    ]
    ..includes = [
      'boost/date_time/microsec_time_clock.hpp',
      'boost/date_time/posix_time/posix_time.hpp',
      'boost/date_time/c_local_time_adjustor.hpp',
    ]
  ];

final conversion = lib('conversion')
  ..namespace = namespace([ 'fcs', 'timestamp' ])
  ..headers = [
    header('conversion')
    ..customBlocks = [ fcbEndNamespace ]
    ..includes = [
      'fcs/timestamp/timestamp.hpp',
      'boost/date_time/posix_time/time_formatters.hpp',
      'regex',
    ]
  ];

addItems() => installation.addLibs([timestamp, conversion]);

main() {
  addItems();
  installation.generate();
}