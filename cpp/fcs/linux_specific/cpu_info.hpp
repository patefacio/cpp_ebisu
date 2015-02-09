#ifndef __FCS_LINUX_SPECIFIC_CPU_INFO_HPP__
#define __FCS_LINUX_SPECIFIC_CPU_INFO_HPP__

#include "fcs/linux_specific/linux_exceptions.hpp"
#include "fcs/utils/exception/make_exception.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <fstream>
#include <iterator>
#include <string>
#include <sys/types.h>
#include <unistd.h>

namespace fcs {
namespace linux_specific {
/**
 Information stored on a processor basis in cpuinfo.
 The fields in this class are dynamically generated from parsing
 cpuinfo.
*/
class Processor {
 public:
  using Proc_key_to_value_t = std::map<std::string, std::string>;

  //! getter for proc_key_to_value_ (access is Ro)
  Proc_key_to_value_t const& proc_key_to_value() const {
    return proc_key_to_value_;
  }

  //! getter for processor_ (access is Ro)
  std::string const& processor() const { return processor_; }

 private:
  Proc_key_to_value_t proc_key_to_value_{};
  std::string processor_{};
};

using Processor_list_t = std::vector<Processor>;

/**
 Class to parse the cpuinfo file. This might be of use to interrogate
 from code the stats of the machine for better enabling <apple to apple>
 comparisons.
*/
class Cpu_info {
 public:
  static Cpu_info& instance() {
    static Cpu_info instance_s;
    return instance_s;
  }

  //! getter for processors_ (access is Ro)
  Processor_list_t const& processors() const { return processors_; }

 private:
  // custom <ClsPrivate Cpu_info>

  std::string read_cpu_info() {}

  // end <ClsPrivate Cpu_info>

  Cpu_info() {
    // custom <Cpu_info defaultCtor>

    std::string contents{read_cpu_info()};

    // end <Cpu_info defaultCtor>
  }

  Processor_list_t processors_{};
};

}  // namespace linux_specific
}  // namespace fcs
#endif  // __FCS_LINUX_SPECIFIC_CPU_INFO_HPP__
