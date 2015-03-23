library libs.linux_specific;

import 'dart:io';
import 'package:ebisu/ebisu.dart';
import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/fcs_installation.dart';

/// Parses /proc/cpuinfo and for the processor section of the first
/// processor returns the set of entries. For example, returns:
///
///    [ 'processor', 'vendor_id', 'cpu_family',...]
///
/// for the following *cpuinfo* contents:
///
///    processor	: 0
///    vendor_id	: GenuineIntel
///    cpu family	: 6
///    model		: 69
///    model name	: Intel(R) Core(TM) i7-4510U CPU @ 2.00GHz
///    stepping	: 1
///    microcode	: 0x17
///    cpu MHz		: 2000.000
///    cache size	: 4096 KB
///    ...
///
get processorEntries {
  final procRe = new RegExp(r'processor\s*:\s*');
  final byLineRe = new RegExp(r'\n');

  return new File('/proc/cpuinfo')
  .readAsStringSync()
  .split(procRe)
  .skip(1)  // skip first empty element post-split
  .take(1)  // take first processor entry
  .map((String proc) =>
      proc
      .split(byLineRe)
      .skip(1)
      .where((String line) => line.length > 0)
      .map((String line) =>
        line
          .split(r':')
          .take(1)
          .map((String word) =>
              word
              .trim()
              .toLowerCase()
              .replaceAll(' ', '_'))
          .first)
      .toList())
  .first;
}

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
      ..includesTest = true
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
        ..type = 'mode_t'..access = ro..hasNoInit = true
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
        base('boost::exception')..isVirtual = true..access = public,
        base('std::exception')..isVirtual = true..access = public,
      ]
    ],
    header('cpu_info')
    ..withTest((Test test) {
      test.includes.addAll(['iostream', 'sstream']);
    })
    ..includes = [
      'fcs/linux_specific/linux_exceptions.hpp',
      'fcs/utils/streamers/map.hpp',
      'fcs/utils/streamers/vector.hpp',
      'fcs/utils/exception/make_exception.hpp',
      'fstream', 'iterator', 'boost/regex.hpp', 'boost/thread.hpp',
      'boost/lexical_cast.hpp',
      'sys/types.h', 'unistd.h', 'boost/algorithm/string.hpp',
    ]
    ..classes = [
      class_('processor')
      ..isStreamable = true
      ..usesStreamers = true
      ..usingsPostDecl = [ 'Processor_list_t = std::vector< Processor >' ]
      ..memberCtors = [ memberCtor(['processor', 'proc_map']) ]
      ..withCustomBlock(clsPublic, (CodeBlock cb) {
        cb.snippets
          .add(
              br(processorEntries
                  .map((String entry) {
                    return '''
std::string $entry() const {
  auto found = proc_map_.find("$entry");
  return (found != proc_map_.end())? found->second : "";
}
''';
                  })));
      })
      ..descr = '''
Information stored on a processor basis in cpuinfo.
The fields in this class are dynamically generated from parsing
cpuinfo.'''
      ..usings = [ 'Proc_map_t = std::map< std::string, std::string >' ]
      ..members = [
        member('proc_map')
        ..type = 'Proc_map_t'..isByRef = true..access = ro,
        member('processor')
        ..type = 'int'..access = ro
      ],
      class_('cpu_info')
      ..isStreamable = true
      ..usesStreamers = true
      ..includesTest = true
      ..descr = '''
Class to parse the cpuinfo file. This might be of use to interrogate
from code the stats of the machine for better enabling <apple to apple>
comparisons.
'''
      ..isSingleton = true
      ..withDefaultCtor((defaultCtor) =>
          defaultCtor..hasCustom = true)
      ..customBlocks = [ clsPrivate ]
      ..members = [
        member('processors')
        ..type = 'Processor_list_t'..isByRef = true..access = ro
      ],
    ]

  ];

addItems() => fcsInstallation.addLibs([linux_specific]);

main() {
  addItems();
  fcsInstallation.generate();
}