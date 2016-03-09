library libs.logger;

import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

final environment = lib('environment')
  ..namespace = namespace(['ebisu', 'environment'])
  ..headers = [
    header('environment')
      ..classes = [
        class_('environment')
          ..includes.addAll([
            'ebisu/utils/streamers/vector.hpp',
            'ebisu/utils/streamers/map.hpp',
            'boost/filesystem.hpp',
            'boost/regex.hpp',
            'unistd.h',
            'sstream',
            'vector',
            'exception',
          ])
          ..defaultCtor.customCodeBlock.snippets.add('read_environment();')
          ..customBlocks = [clsPrivate]
          ..doc = '''
Singleton that when initialized churns through various environment variables
like LD_LIBRARY_PATH, MANPATH, PATH, etc...
The purpose is to make the paths those variables refer to available to code.'''
          ..usings = [
            using('environment_map', 'std::map< std::string, std::string >'),
            using('path_variable_set', 'std::set< std::string >'),
            using('path', 'boost::filesystem::path'),
            using('path_list', 'std::vector< Path_t >'),
            using('path_variable_map', 'std::map< std::string, Path_list_t >'),
          ]
          ..isSingleton = true
          ..usesStreamers = true
          ..members = [
            member('environment')
              ..type = #u.environment_map
              ..isByRef = true
              ..access = ro,
            member('path_variable_map')
              ..type = #u.path_variable_map
              ..isByRef = true
              ..access = ro,
          ],
      ]
      ..testScenarios = [testScenario('read environment'),],
  ];

addItems() => ebisuInstallation.addLibs([environment]);

main() {
  addItems();
  ebisuInstallation.generate();
}
