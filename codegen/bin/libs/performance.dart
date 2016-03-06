library libs.performance;

import "package:logging/logging.dart";
import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final performance = lib('performance')
  ..namespace = namespace([ 'ebisu', 'performance' ])
  ..withStandardizedHeader(libCommonHeader, (Header header) {
    //print(header.contents);
  })
  ..version = '0.0.1'
  ..libInitializer
  ..requiresLogging = true
  ..headers = [
    header('block_timers')
    ..includes = [
      'boost/call_traits.hpp',
      'chrono'
    ]
    ..classes = [

      class_('block_timer')
      ..brief = 'Times a block of code'
      ..doc = '''
Uses RIIA to start a timer on construction, stop the timer on
destruction and calculate the difference. To be useful, the duration
needs to exist beyond the timing, so it is passed in by reference.

Rather than simply assign the timing to the duration, it is added so
the duration can be used with multiple timers.
'''
      ..usings = [
        using('clock', 'CLOCK'),
        using('time_point', 'typename Clock_t::time_point'),
        using('duration', 'typename Clock_t::duration'),
      ]
      ..template = [
        'typename CLOCK = std::chrono::high_resolution_clock',
      ]
      ..memberCtors = [ memberCtor(['duration']) ]
      ..members = [
        member('start')
        ..doc = 'Start of timing - stamped on construction'
        ..type = 'Time_point_t'
        ..init = 'Clock_t::now()',
        member('stop')
        ..doc = 'Stop of timing - stamped on destruction'
        ..type = 'Time_point_t',
        member('duration')
        ..type = 'Duration_t'
        ..refType = ref,
      ]
      ..customBlocks = [ clsPublic ]
      ..testScenarios = [
        testScenario('block timer',
            given('a block timer')
            ..whens = [
                when('work is done in the block')
                ..thens = [then('that work is timed')]
            ])
      ],

      class_('block_timer_logger')
      ..brief = 'Logs the results of timing a block of code'
      ..template = [ 'typename BLOCK_TIMER = Block_timer<>' ]
      ..usings = [
        using('clock', 'CLOCK'),
        using('time_point', 'typename Clock_t::time_point'),
        using('duration', 'typename Clock_t::duration'),
      ]
      ..template = [
        'typename CLOCK = std::chrono::high_resolution_clock',
      ]
      ..customBlocks = [ clsPublic ]
      ..memberCtors = [
        memberCtor([
          'out',
          memberCtorParm('description')..defaultValue = '""'
        ]) ]
      ..members = [
        member('description')
        ..doc = 'Text describing block being timed'
        ..type = 'std::string',
        member('out')
        ..doc = 'Stream to log results'
        ..type = 'std::ostream'
        ..refType = ref
        ..isByRef = true,
        member('start')
        ..doc = 'Start of timing - stamped on construction'
        ..type = 'Time_point_t'
        ..init = 'Clock_t::now()',
        member('stop')
        ..doc = 'Stop of timing - stamped on destruction'
        ..type = 'Time_point_t',
        member('duration')
        ..doc = 'Duration of a timed block - value to be logged at destruction'
        ..type = 'Duration_t'
        ..access = ia
      ]
      ..testScenarios = [
        testScenario('block timer logger',
            given('a block timer')
            ..whens = [
                when('work is done in the block')
                ..thens = [then('the timed values are logged')]
            ])
      ],
    ],

    header('block_rusage')
    ..brief = 'Utilities for tracking resource utilization (Linux)'
    ..customBlocks = [fcbBeginNamespace, fcbEndNamespace]
    ..includes = [
      'sys/time.h',
      'sys/resource.h',
      'ebisu/utils/block_indenter.hpp',
    ]
    ..classes = [

      class_('rusage_delta')
      ..doc = 'Tracks start/stop and delta on rusage'
      ..customBlocks = [ clsPublic ]
      ..isStreamable = true
      ..members = [
        member('start')
        ..doc = 'Result of ru at start of block'
        ..type = 'rusage'
        ..cppAccess = public,
        member('stop')
        ..doc = 'Result of ru at end of block'
        ..type = 'rusage'
        ..cppAccess = public,
        member('delta')
        ..doc = 'Diff - stop - start'
        ..type = 'rusage'
        ..cppAccess = public,
      ],

      class_('block_rusage')
      ..doc = 'Tracks resource utilization over a block'
      ..memberCtors = [
        memberCtor(['rusageDelta'])
        ..includesProtectBlock = true
      ]
      ..customBlocks = [ clsPublic ]
      ..members = [
        member('rusage_delta')
        ..type = 'Rusage_delta'
        ..refType = ref
        ..isByRef = true,
      ]
      ..testScenarios = [
        testScenario('block rusage',
            given('a block rusage')
            ..whens = [
                when('work is done in the block')
                ..thens = [then('the rusage delta is captured')]
            ])
      ],
    ]
  ];

addItems() => ebisuInstallation.addLib(performance);

main() {
  addItems();
  Logger.root.onRecord.listen((LogRecord r) =>
      print("${r.loggerName} [${r.level}]:\t${r.message}"));
  Logger.root.level = Level.OFF;
  ebisuInstallation.generate();
}