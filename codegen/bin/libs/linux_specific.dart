library libs.linux_specific;

import 'dart:io';
import 'package:ebisu/ebisu.dart';
import 'package:ebisu_cpp/ebisu_cpp.dart';
import '../../lib/ebisu_installation.dart';

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
  ..requiresLogging = true
  ..namespace = namespace([ 'ebisu', 'linux_specific' ])
  ..headers = [
    header('application_signal_handler')
    ..doc = 'Support for catching signals and associating handlers'
    ..includes = [ 'csignal', 'mutex' ]
    ..doc = 'Support for consistent catching/handling of signals'
    ..testScenarios = [
      testScenario('catching signal', [
        given('registered handler', [
          when('signal sent', [
            then('signal handled')
          ])
        ])
      ])
    ]
    ..classes = [
      class_('application_signal_handler')
      ..doc = '''
A singleton class to allow registration of common interrupting signal handlers.

  - SIGHUP
  - SIGINT
  - SIGTERM
  - SIGUSR1
  - SIGKILL

The singleton creates a thread which waits for signals. Clients can register
handlers with [Application_signal_handler::add_handler]. When a signal is
caught, the handlers are each all called in turn. For all signals except SIGKILL, f
any of the registered handlers returns true, the signal handler loop carries on
as before. If all handlers return true, the [Application_signal_handler] is done
and the thread will complete.

If SIGKILL is caught, the handlers are each called in turn and the loop is
exited regardless of the handlers return values. This allows handlers to attempt
cleanup before exit.

A typical use case would be an application that you might not want to be killed
with Ctrl-C. To achieve this include the header in the file with
*main*. Register a handler to deal with the signal. Prior to exiting the *main*
call [Application_signal_handler::stop_handler_thread].
'''
      ..customBlocks = [ clsPublic, clsPrivate ]
      ..template = [
        'typename LOCK_TYPE = std::mutex',
        'typename GUARD_TYPE = std::lock_guard< LOCK_TYPE >',
      ]
      ..defaultCtor.includesProtectBlock = true
      ..dtor.includesProtectBlock = true
      ..usings = [
        using('thread', 'std::thread'),
        usingUptr('thread', 'Thread_t'),
        using('lock_type', 'LOCK_TYPE'),
        using('guard_type', 'GUARD_TYPE'),
        using('handler_function', 'std::function< bool(int) >'),
        using('handler_function_list', 'std::vector< Handler_function_t >'),
      ]
      ..isSingleton = true
      ..members = [
        member('handler_function_list')
        ..doc = 'User defined handler functions registered with [add_handler]'
        ..type='Handler_function_list_t',
        member('instance_lock')
        ..doc = 'Lock protecting access to [handler_function_list_t]'
        ..type='Lock_type_t',
        member('handler_thread')
        ..doc = 'Thread that calls sigwait to process signals'
        ..type = 'Thread_uptr_t',
        member('exit_requested')
        ..doc = 'Used to cleanly exit via signal'
        ..init = false,
      ],

      class_('application_signal_handler_exit')
      ..doc = '''
Class to clean up the application handler thread.

Use as an automatic variable in main to ensure cleanup.
'''
      ..dtor.includesProtectBlock = true
      ..defaultCtor.usesDefault = true
      ..isNoncopyable = true,

    ],

    header('umask_scoped_set')
    ..includes = [
      'sys/types.h',
      'sys/stat.h',
    ]
    ..testScenarios = [
      testScenario('unit_test_umask_scoped_set',
          given('current umask is something',
              when('setting umask to something else',
                  then('it is set and reverted on exit')))),
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
        ..isExplicit = true
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
      'ebisu/linux_specific/linux_exceptions.hpp',
      'ebisu/utils/streamers/map.hpp',
      'ebisu/utils/streamers/vector.hpp',
      'ebisu/utils/exception/make_exception.hpp',
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
      ..testScenarios = [
        testScenario('cpu info')
        ..givens = [
          given('the single cpu_info instance',
              when('accessing processors',
                  [
                    then('some processors are found'),
                    then('the first processor has flags'),
                    then('the fpu flag is yes'),
                  ])
                )
        ]
      ]
      ..isStreamable = true
      ..usesStreamers = true
      ..descr = '''
Class to parse the cpuinfo file. This might be of use to interrogate
from code the stats of the machine for better enabling <apple to apple>
comparisons.
'''
      ..isSingleton = true
      ..withDefaultCtor((defaultCtor) =>
          defaultCtor..includesProtectBlock = true)
      ..customBlocks = [ clsPrivate ]
      ..members = [
        member('processors')
        ..type = 'Processor_list_t'..isByRef = true..access = ro
      ],
    ]

  ];

addItems() => ebisuInstallation.addLibs([linux_specific]);

main() {
  addItems();
  ebisuInstallation.generate();
}