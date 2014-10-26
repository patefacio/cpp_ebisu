library bin.raii;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final raii = lib('raii')
  ..namespace = namespace([ 'fcs', 'raii' ])
  ..headers = [
    header('change_tracker')
    ..classes = [
      class_('change_tracker')
      ..members = [
        member('saved_value')..type = 'T',
        member('target')..type = 'T',
      ],
      class_('change_tracker_next_value'),
    ],
    header('change_until_end_of_block')
    ..classes = [
      class_('change_until_end_of_block'),
    ],
    header('api_initializer')
    ..includes = [ 'vector', 'map' ]
    ..usings = [
      'Void_func_t = void (*)(void)',
    ]
    ..includeTest = true
    ..classes = [
      class_('functor_scope_exit')
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