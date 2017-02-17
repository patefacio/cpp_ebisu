#ifndef __EBISU_PERFORMANCE_BLOCK_RUSAGE_HPP__
#define __EBISU_PERFORMANCE_BLOCK_RUSAGE_HPP__

//! Utilities for tracking resource utilization (Linux)

#include "ebisu/performance/performance_common.hpp"
#include "ebisu/performance/performance_initialization.hpp"
#include "ebisu/performance/performance_logging.hpp"
#include "ebisu/utils/block_indenter.hpp"
#include <iosfwd>
#include <sys/resource.h>
#include <sys/time.h>

namespace ebisu {
namespace performance {
// custom <FcbBeginNamespace block_rusage>

rusage operator-(rusage stop, rusage start) {
  rusage result;

  result.ru_utime.tv_sec = stop.ru_utime.tv_sec - start.ru_utime.tv_sec;
  result.ru_utime.tv_usec = stop.ru_utime.tv_usec - start.ru_utime.tv_usec;
  result.ru_stime.tv_sec = stop.ru_stime.tv_sec - start.ru_stime.tv_sec;
  result.ru_stime.tv_usec = stop.ru_stime.tv_usec - start.ru_stime.tv_usec;

  result.ru_maxrss = stop.ru_maxrss - start.ru_maxrss;
  result.ru_ixrss = stop.ru_ixrss - start.ru_ixrss;
  result.ru_idrss = stop.ru_idrss - start.ru_idrss;
  result.ru_isrss = stop.ru_isrss - start.ru_isrss;
  result.ru_minflt = stop.ru_minflt - start.ru_minflt;
  result.ru_majflt = stop.ru_majflt - start.ru_majflt;
  result.ru_nswap = stop.ru_nswap - start.ru_nswap;
  result.ru_inblock = stop.ru_inblock - start.ru_inblock;
  result.ru_oublock = stop.ru_oublock - start.ru_oublock;
  result.ru_msgsnd = stop.ru_msgsnd - start.ru_msgsnd;
  result.ru_msgrcv = stop.ru_msgrcv - start.ru_msgrcv;
  result.ru_nsignals = stop.ru_nsignals - start.ru_nsignals;
  result.ru_nvcsw = stop.ru_nvcsw - start.ru_nvcsw;
  result.ru_nivcsw = stop.ru_nivcsw - start.ru_nivcsw;

  return result;
}

std::ostream& operator<<(std::ostream& out, rusage const& r) {
  ebisu::utils::Block_indenter indenter;
  char const* indent(indenter.current_indentation_text());
  out << '\n'
      << indent << " user time:" << r.ru_utime.tv_sec << "(s) "
      << r.ru_utime.tv_usec << "(micro)";
  out << '\n'
      << indent << " system time:" << r.ru_stime.tv_sec << "(s) "
      << r.ru_stime.tv_usec << "(micro)";
  out << '\n' << indent << " maximum resident set size:" << r.ru_maxrss;

  /////////////// unused
  // out << '\n' << indent << " integral shared memory size:" << r.ru_ixrss;
  // out << '\n' << indent << " integral unshared data size:" << r.ru_idrss;
  // out << '\n' << indent << " integral unshared stack size:" << r.ru_isrss;

  out << '\n' << indent << " page reclaims:" << r.ru_minflt;
  out << '\n' << indent << " page faults:" << r.ru_majflt;

  /////////////// unused
  // out << '\n' << indent << " swaps:" << r.ru_nswap;

  out << '\n' << indent << " block input operations:" << r.ru_inblock;
  out << '\n' << indent << " block output operations:" << r.ru_oublock;

  /////////////// unused
  // out << '\n' << indent << " messages sent:" << r.ru_msgsnd;
  // out << '\n' << indent << " messages received:" << r.ru_msgrcv;
  // out << '\n' << indent << " signals received:" << r.ru_nsignals;
  out << '\n' << indent << " voluntary context switches:" << r.ru_nvcsw;
  out << '\n' << indent << " involuntary context switches:" << r.ru_nivcsw;

  return out;
}

// end <FcbBeginNamespace block_rusage>

/**
 Tracks start/stop and delta on rusage
*/
class Rusage_delta {
 public:
  friend inline std::ostream& operator<<(std::ostream& out,
                                         Rusage_delta const& item) {
    out << "Rusage_delta(" << &item << ") {";
    out << "\n  start:" << item.start;
    out << "\n  stop:" << item.stop;
    out << "\n  delta:" << item.delta;
    out << "\n}\n";
    return out;
  }

  // custom <ClsPublic Rusage_delta>
  // end <ClsPublic Rusage_delta>

  /**
   Result of ru at start of block
  */
  rusage start{};

  /**
   Result of ru at end of block
  */
  rusage stop{};

  /**
   Diff - stop - start
  */
  rusage delta{};
};

/**
 Tracks resource utilization over a block
*/
class Block_rusage {
 public:
  Block_rusage(Rusage_delta& rusage_delta) : rusage_delta_(rusage_delta) {
    // custom <Block_rusage(Rusage_delta & rusage_delta)>
    _get_rusage(rusage_delta_.start);
    // end <Block_rusage(Rusage_delta & rusage_delta)>
  }

  // custom <ClsPublic Block_rusage>

  ~Block_rusage() {
    _get_rusage(rusage_delta_.stop);
    rusage_delta_.delta = rusage_delta_.stop - rusage_delta_.start;
  }

  void _get_rusage(rusage& target) {
    int rc(0);
    if (0 != (rc = getrusage(RUSAGE_THREAD, &target))) {
      std::ostringstream msg;
      msg << "Unable to track rusage - rc:" << rc << " errno:" << errno
          << std::endl;
      throw std::runtime_error(msg.str());
    }
  }

  // end <ClsPublic Block_rusage>

 private:
  Rusage_delta& rusage_delta_;
};

// custom <FcbEndNamespace block_rusage>

// end <FcbEndNamespace block_rusage>

}  // namespace performance
}  // namespace ebisu

#endif  // __EBISU_PERFORMANCE_BLOCK_RUSAGE_HPP__
