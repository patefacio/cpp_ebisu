library libs.timestamp;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';
import 'package:logging/logging.dart';

final observer = lib('observer')
  ..namespace = namespace([ 'ebisu', 'patterns' ])
  ..headers = [
    header('observer')
    ..customBlocks = [ fcbEndNamespace ]
    ..usings = [
    ]
    ..includes = [
      'set',
      'boost/call_traits.hpp',
      'boost/type_traits/add_pointer.hpp',
    ]
    ..classes = [
      class_('signaller')
      ..doc = '''
Singaller part of the observer pattern.'''
      ..customBlocks = [ clsPublic ]
      ..template = [
        'typename data',
        'typename object',
        'typename observer_ptr = typename boost::add_pointer< OBSERVER >::type',
        'typename lock_and_guard_traits = utils::synch::Boost_mutex_lock_and_guard_traits_tag',
      ]
      ..usings = [
        using('observer_ptr', 'OBSERVER_PTR'),
        using('lock', 'typename LOCK_AND_GUARD_TRAITS::Lock_t'),
        using('guard', 'typename LOCK_AND_GUARD_TRAITS::Guard_t'),
        using('observer_list', 'std::vector<Observer_ptr>'),
      ]
      ..members = [
        member('observers')
        ..doc = 'Collection of observers to be signalled'
        ..type = 'Observer_list_t',
        member('lock')
        ..doc = 'Lock to protect the observer container'
        ..type = 'Lock_t',
      ],
      class_('signaller_prioritized')
      ..doc = '''
Signaller part of observer pattern, where observers are kept sorted by priority'''
      ..customBlocks = [ clsPublic ]
      ..template = [
        'typename data',
        'typename observer',
        'typename observer_ptr = typename boost::add_pointer< OBSERVER >::type',
        'typename lock_and_guard_traits = utils::synch::Boost_mutex_lock_and_guard_traits_tag',
      ]
      ..usings = [
        using('observer_ptr', 'OBSERVER_PTR'),
        using('lock', 'typename LOCK_AND_GUARD_TRAITS::Lock_t'),
        using('guard', 'typename LOCK_AND_GUARD_TRAITS::Guard_t'),
        using('priority_observer', 'std::pair<int, Observer_ptr_t>'),
        using('observer_list', 'std::vector<Observer_ptr_t>'),
      ]

    ],
  ];

addItems() => ebisuInstallation.addLibs([observer]);

main() {
  Logger.root
    ..onRecord.listen((LogRecord r) =>
      print("${r.loggerName} [${r.level}]:\t${r.message}"))
    ..level = Level.OFF;

  addItems();
  ebisuInstallation.generate();
}