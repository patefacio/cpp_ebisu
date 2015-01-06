library bin.raii;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final raii = lib('raii')
  ..namespace = namespace([ 'fcs', 'raii' ])
  ..headers = [
    header('change_tracker')
    ..includes = [ 'boost/call_traits.hpp' ]
    ..classes = [
      class_('change_tracker')
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
      ..descr = '''
Uses a ChangeTracker to track current/previous values of a type and
ensures that on destruction the previous value becomes the current
value and the current value will be assigned the next value.'''
      ..template = [ 'typename T' ]
      ..usings = [ 'Change_tracker_t = Change_tracker< T >' ]
      ..customBlocks = [clsPublic]
      ..includeTest = true
      ..members = [
        member('tracker')..type = 'Change_tracker_t'
        ..byRef = true
        ..refType = ref..access = ro,
        member('next_value')..type = 'T'..access = ro,
      ],
      class_('change_until_end_of_block')
      ..descr = '''
Stores the current state, changes that state to a new value and on
destruction restores the original state.'''
      ..template = [ 'typename T' ]
      ..customBlocks = [clsPublic]
      ..includeTest = true
      ..members = [
        member('target')..type = 'T'..refType = ref..access = ro,
        member('saved_value')..type = 'T'..access = ro,
      ],
    ],
    header('api_initializer')
    ..test.customBlocks = [ fcbPreNamespace ]
    ..test.includes.addAll(['vector', 'fcs/utils/streamers/containers.hpp', ])
    ..includes = [ 'list', 'map', 'memory' ]
    ..usings = [
      'Void_func_t = void (*)(void)',
    ]
    ..classes = [
      class_('functor_scope_exit')
      ..includeTest = true
      ..template = [ 'typename FUNCTOR = Void_func_t' ]
      ..usings = [ 'Functor_t = FUNCTOR' ]
      ..customBlocks = [ clsPublic ]
      ..memberCtors = [ memberCtor(['functor']) ]
      ..members = [
        member('functor')..type = 'Functor_t'..noInit = true..access = ro,
      ],
      class_('api_initializer_registry')
      ..descr = '''
For api's that need some form of initialization/uninitialization to be performed.
'''
      ..customBlocks = [ clsPublic ]
      ..usings = [
        'Init_func_t = INIT_FUNC',
        'Uninit_func_t = UNINIT_FUNC',
        'Functor_scope_exit_t = Functor_scope_exit< Uninit_func_t >',
        'Uninit_wrapper_ptr = std::shared_ptr< Functor_scope_exit_t >',
        'Uninit_list_t = std::list< Uninit_wrapper_ptr >',
        'Registry_t = std::map< Init_func_t, Uninit_wrapper_ptr >',
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

addItems() => installation.addLib(raii);

main() {
  addItems();
  installation.generate();
}