library bin.orm;

import 'package:ebisu_cpp/cpp.dart';
import '../../lib/installation.dart';

final linux_specific = lib('linux_specific')
  ..namespace = namespace([ 'fcs', 'linux_specific' ])
  ..headers = [
    header('umask_scoped_set')
    ..includes = [
      'sys/types.h',
      'sys/stat.h',
    ]
    ..classes = [
      class_('umask_scoped_set')
      ..descr = '''
A typical use of this is to set the umask for a process to provide
settings of system resources (files, mutexes, mappings,...)  to allow
group members in. For instance, an app may create shared memory, and
therefore an entry in /dev/shm, but to share it the permissions must
work. umask settings play a role.'''
      ..memberCtors = [
        memberCtor([
          memberCtorParm('previous_mode')
          ..parmDecl = 'mode_t new_mode'
          ..init = 'umask(new_mode)'
        ])
      ]
      ..customBlocks = [ clsPublic ]
      ..members = [
        member('previous_mode')
        ..descr = 'Original mode, restored to on destruction'
        ..type = 'mode_t'..access = ro..noInit = true
      ]
    ],
    header('linux_exceptions')
    ..includes = [
      'boost/exception/exception.hpp',
      'boost/exception/error_info.hpp',
      'exception',
      'string',
    ]
    ..classes = [
      class_('system_file_parse_exception')
      ..doc = 'Indicates parsing of system file failed'
      ..usings = ['filename_tag = boost::error_info<struct tag_filename_tag, std::string>']
      ..bases = [
        base('boost::exception')..virtual = true..access = public,
        base('std::exception')..virtual = true..access = public,
      ]
    ],
    header('cpu_info')
    ..withTest((Test test) {
      test
        ..enums.add(
            enum_('side')
            ..values = [ 'bid_side', 'ask_side' ])
        ..includes.add('iostream');
    })
    ..includes = [
      'fcs/linux_specific/linux_exceptions.hpp',
      'fcs/utils/exception/make_exception.hpp',
      'fstream', 'iterator', 'boost/regex.hpp', 'boost/thread.hpp',
      'sys/types.h', 'unistd.h', 'boost/algorithm/string.hpp',
    ]
    ..classes = [
      class_('processor')
      ..usingsPostDecl = [ 'Processor_list_t = std::vector< Processor >' ]
      ..descr = '''
Information stored on a processor basis in cpuinfo.
The fields in this class are dynamically generated from parsing
cpuinfo.'''
      ..usings = [ 'Proc_key_to_value_t = std::map< std::string, std::string >' ]
      ..members = [
        member('proc_key_to_value')
        ..type = 'Proc_key_to_value_t'..byRef = true..access = ro,
        member('processor')
        ..type = 'std::string'..access = ro
      ],
      class_('cpu_info')
      ..includeTest = true
      ..descr = '''
Class to parse the cpuinfo file. This might be of use to interrogate
from code the stats of the machine for better enabling <apple to apple>
comparisons.'''
      ..isSingleton = true
      ..withDefaultCtor((defaultCtor) =>
          defaultCtor..hasCustom = true)
      ..customBlocks = [ clsPrivate ]
      ..members = [
        member('processors')
        ..type = 'Processor_list_t'..byRef = true..access = ro
      ],
    ]

  ];

addItems() => installation.addLibs([linux_specific]);

main() {
  addItems();
  installation.generate();
}