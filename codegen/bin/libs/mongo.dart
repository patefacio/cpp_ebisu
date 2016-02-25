library libs.orm;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final mongo_utils = lib('mongo')
  ..requiresLogging = true
  ..namespace = namespace(['ebisu', 'mongo'])
  ..headers = [
    header('connection_registry')
    ..includes = [
      'mutex',
      'ebisu/mongo/mongo_ini.hpp',
      'mongo/client/dbclient.h',
    ]
    ..classes = [
      class_('connection_registry')
      ..isSingleton = true
      ..usings.addAll(standardMutexUsings)
      ..usings.addAll([
        using('database_configuration_map', 'Mongo_ini_parser::Database_configuration_map_t'),
        usingPtr('tss_connection', 'boost::thread_specific_ptr< ::mongo::DBClientConnection >'),
        using('thread_connection_map', 'std::map<std::string, Tss_connection_ptr_t>'),
      ])
      ..template = standardMutexTemplateParms
      ..members = [
        member('database_configuration_map')..type = 'Database_configuration_map_t',
        member('lock')..type = 'Lock_t',
        member('thread_connection_map')..type = 'Thread_connection_map_t',
      ],
    ],
    header('mongo_ini')
    ..includes = [
      'boost/program_options.hpp',
      'boost/program_options/parsers.hpp',
      'boost/filesystem/path.hpp',
      'boost/thread.hpp',
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
      ..customBlocks = [ clsPublic ]
      ..usings = [
        using('database_configuration_map', 'std::map< std::string, Mongo_database_config >'),
      ]
      ..members = [
        member('database_configuration_map')..type = 'Database_configuration_map_t',
        member('mongo_options_description')
        ..type = 'boost::program_options::options_description',
        member('ini_file_path')
        ..doc = r'The ini found when searching in $HOME and environment'
        ..type = 'std::string',
      ]

    ]
  ]
  ..testScenarios = [
    /// TODO Add back after move to mongo-cxx driver
    // testScenario('connection_registry')
    // ..includes.addAll([
    //   'ebisu/mongo/connection_registry.hpp'
    // ]),
    // testScenario('mongo_ini_parser')
    // ..includes.addAll([
    //   'ebisu/mongo/mongo_ini.hpp'
    // ])
  ];

addItems() => ebisuInstallation.addLibs([mongo_utils]);

main() {
  addItems();
  ebisuInstallation.generate();
}
