library libs.timestamp;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final timestamp = lib('timestamp')
  ..namespace = namespace([ 'ebisu', 'timestamp' ])
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
    ],
    header('cereal')
    ..includes = [ 'ebisu/timestamp/timestamp.hpp', 'cstdint' ]
    ..customBlocks = [ fcbPostNamespace ]
  ];

final conversion = lib('conversion')
  ..namespace = namespace([ 'ebisu', 'timestamp' ])
  ..headers = [
    header('conversion')
    ..customBlocks = [ fcbEndNamespace ]
    ..includes = [
      'ebisu/timestamp/timestamp.hpp',
      'boost/date_time/posix_time/time_formatters.hpp',
      'boost/regex.hpp',
    ]
  ];

addItems() => ebisuInstallation.addLibs([timestamp, conversion]);

main() {
  addItems();
  ebisuInstallation.generate();
}