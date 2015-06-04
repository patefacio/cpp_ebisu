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
      ..usings = [
        using('clock', 'CLOCK'),
        using('time_point', 'TIME_POINT'),
        using('duration', 'DURATION'),
      ]
      ..template = [
        'typename CLOCK = std::chrono::high_resolution_clock',
        'typename TIME_POINT = typename CLOCK::time_point',
        'typename DURATION = typename CLOCK::duration',
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
        using('time_point', 'TIME_POINT'),
        using('duration', 'DURATION'),
      ]
      ..template = [
        'typename CLOCK = std::chrono::high_resolution_clock',
        'typename TIME_POINT = typename CLOCK::time_point',
        'typename DURATION = typename CLOCK::duration',
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

      class_('streaming_block_timer')
      ..brief = 'Times a block of code and via RIIA logs results'
      ..descr = '''
Times a block and logs results
'''
      ..template = [ 'typename T' ]
      ..customBlocks = [clsPublic]
      ..members = [
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