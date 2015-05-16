library libs.raii;

import "package:logging/logging.dart";
import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/fcs_installation.dart';

final raii = lib('raii')
  ..namespace = namespace([ 'fcs', 'raii' ])
  ..withStandardizedHeader(libCommonHeader, (Header header) {
    //print(header.contents);
  })
  ..version = '0.0.1'
  ..libInitializer
  ..requiresLogging = true
  ..headers = [
    header('change_tracker')
    ..includes = [ 'boost/call_traits.hpp' ]
    ..classes = [

      class_('change_tracker')
      ..brief = 'Track updates to variable.'
      ..descr = '''
Tracks current/previous values of the given type of data. For some
algorithms it is useful to be able to examine/perform logic on
current value and compare or evalutate how it has changed since
previous value.'''
      ..template = [ 'typename T' ]
      ..customBlocks = [clsPublic]
      ..members = [
        member('current')..type = 'T'..access = ro,
        member('previous')..type = 'T'..access = ro,
      ],

      class_('change_tracker_next_value')
      ..brief = 'Work with current value, ensure next value is applied on scope exit.'
      ..descr = '''
Uses a ChangeTracker to track current/previous values of a type and
ensures that on destruction the previous value becomes the current
value and the current value will be assigned the next value.'''
      ..template = [ 'typename T' ]
      ..usings = [ using('change_tracker', 'Change_tracker< T >')]
      ..customBlocks = [clsPublic]
      ..members = [
        member('tracker')..type = 'Change_tracker_t'
        ..isByRef = true
        ..refType = ref..access = ro,
        member('next_value')..type = 'T'..access = ro,
      ]
      ..testScenarios = [
        testScenario('change_tracker_next_value')
        ..givens = [
          given('an int change_tracker assigned to one')
          ..whens = [
            when('a block sets current_value to one and next_value to three')
            ..thens = [
              then('when leaving block previous is one and current is three'),
            ]
          ]
        ]
      ],

      class_('change_until_end_of_block')
      ..brief = 'Change and use value within block, revert to original on scope exit.'
      ..descr = '''
Stores the current state, changes that state to a new value and on
destruction restores the original state.'''
      ..template = [ 'typename T' ]
      ..customBlocks = [clsPublic]
      ..testScenarios = [
        testScenario('change_until_end_of_block')
        ..givens = [
          given('an int initialized to one')
          ..whens = [
            when('a block changes the value to three')
            ..thens = [
              then('after the block exits it reverts to one'),
            ]
          ]
        ]
      ]
      ..members = [
        member('target')
        ..doc = 'Reference to the item being changed for duration of block'
        ..type = 'T'..refType = ref..access = ro,
        member('saved_value')
        ..doc = 'Value saved on construction and used to reset on block exit'
        ..type = 'T'
        ..access = ro,
      ],
    ],
    header('api_initializer')
    ..test.customBlocks = [ fcbPreNamespace ]
    ..test.includes.addAll(['vector'])
    ..includes = [ 'list', 'map', 'memory' ]
    ..excludeStandardizedHeader(libInitializationHeader)
    ..usings = [ using('void_func', 'void (*)(void)') ]
    ..classes = [
      class_('functor_scope_exit')
      ..brief = 'Ensure functor is run on obect destruction'
      ..testScenarios = [
        testScenario('functor runs on block exit',
            given('functor in block',
                when('block has exited',
                    then('functor runs'))))
      ]
      ..template = [ 'typename FUNCTOR = Void_func_t' ]
      ..usings = [ using('functor', 'FUNCTOR') ]
      ..customBlocks = [ clsPublic ]
      ..memberCtors = [
        memberCtor(['functor'])
        ..isExplicit = true
        ..isLogged = true
      ]
      ..members = [
        member('functor')
        ..doc = 'Function object to run on exit'
        ..type = 'Functor_t'
        ..hasNoInit = true..access = ro,
      ],
      class_('api_initializer_registry')
      ..brief = 'Singleton registry for Apis requiring consistent init/uninit behavior'
      ..descr = '''
For APIs that need some form of initialization/uninitialization to be
performed.
'''
      ..customBlocks = [ clsPublic ]
      ..defaultCtor.isLogged = true
      ..usings = [
        'Init_func = INIT_FUNC',
        'Uninit_func = UNINIT_FUNC',
        'Functor_scope_exit = Functor_scope_exit< Uninit_func_t >',
        'Uninit_wrapper_ptr = std::shared_ptr< Functor_scope_exit_t >',
        'Uninit_list = std::list< Uninit_wrapper_ptr_t >',
        'Registry = std::map< Init_func_t, Uninit_wrapper_ptr_t >',
      ]
      ..isSingleton = true
      ..template = [
        'typename INIT_FUNC = Void_func_t',
        'typename UNINIT_FUNC = Void_func_t',
      ]
      ..members = [
        member('registry')..type = 'Registry_t',
        member('registry_ordered')..type = 'Uninit_list_t',
      ],
      class_('api_initializer')
      ..brief = 'Provide consistent *init*/*uninit* behavior'
      ..usings = [
        'Api_initializer_registry_t = Api_initializer_registry< INIT_FUNC, UNINIT_FUNC >'
      ]
      ..template = [
        'typename INIT_FUNC = Void_func_t',
        'typename UNINIT_FUNC = Void_func_t',
      ]
      ..customBlocks = [ clsPublic ]
    ]
  ];

addItems() => fcsInstallation.addLib(raii);

main() {
  addItems();
  Logger.root.onRecord.listen((LogRecord r) =>
      print("${r.loggerName} [${r.level}]:\t${r.message}"));
  Logger.root.level = Level.OFF;
  fcsInstallation.generate();
}