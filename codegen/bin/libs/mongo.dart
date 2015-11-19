library libs.orm;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final mongo_utils = lib('mongo')
  ..requiresLogging = true
  ..namespace = namespace(['ebisu', 'mongo'])
  ..headers = [
    header('connection_registry')
    ..includes = [
      'mutex'
    ]
    ..classes = [
      class_('connection_registry')
      ..isSingleton = true
      ..usings.addAll(standardMutexUsings)
      ..template = standardMutexTemplateParms,
    ],
    header('mongo_ini')
    ..includes = [
      'boost/program_options.hpp',
      'boost/program_options/parsers.hpp',
    ]
    ..classes = [
      class_('mongo_database_config')
      ..isImmutable = true
      ..members = [
        member('server')..type = 'std::string',
        member('user')..type = 'std::string',
        member('password')..type = 'std::string'
      ],
      class_('mongo_ini_parser')
      ..defaultCtor.tag = 'parse ini file'
      ..usings = [
        using('database_configuration_map', 'std::map< std::string, Mongo_database_config >'),
      ]
      ..members = [
        member('database_configuration_map')..type = 'Database_configuration_map_t',
        member('mongo_options_description')
        ..type = 'boost::program_options::options_description'
      ]

    ]
  ]
  ..testScenarios = [
    testScenario('connection_registry')
    ..includes.addAll([
      'ebisu/mongo/connection_registry.hpp'
    ]),
    testScenario('mongo_ini_parser')
    ..includes.addAll([
      'ebisu/mongo/mongo_ini.hpp'
    ])
  ];

addItems() => ebisuInstallation.addLibs([mongo_utils]);

main() {
  addItems();
  ebisuInstallation.generate();
}
