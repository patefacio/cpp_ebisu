library libs.logger;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final logger = lib('logger')
  ..namespace = namespace([ 'ebisu', 'logger' ])
  ..headers = [
    header('logger')
    ..doc = '''
Exposes simple templated logging api modeled on spdlog.

The idea is that spdlog should work in most cases. But the level of indirection
offered by this templatized logger allows log statements fully optimized out
when a *null logger* implementation is used.
'''
    ..customBlocks = [ fcbEndNamespace ]
    ..classes = [
      class_('logger')
      ..template = [ 'typename LOGGER_IMPL = std::shared_ptr<spdlog::logger>' ]
      ..customBlocks = [ clsPublic ]
      ..memberCtors = [ memberCtor(['impl']) ]
      ..usings = [
        using('logger_impl', 'LOGGER_IMPL'),
      ]
      ..members = [
        member('impl')..type = 'Logger_impl_t',
      ],

      class_('null_logger_impl')
      ..customBlocks = [ clsPublic ],

    ]
    ..usings = [
    ]
    ..includes = [
      'memory',
      'spdlog/spdlog.h'
    ]
    ..testScenarios = [
      testScenario('default_logger'),
      testScenario('null_logger'),
    ],
  ];

addItems() => ebisuInstallation.addLibs([logger]);

main() {
  addItems();
  ebisuInstallation.generate();
}