#ifndef __EBISU_LINUX_SPECIFIC_CPU_INFO_HPP__
#define __EBISU_LINUX_SPECIFIC_CPU_INFO_HPP__

#include "ebisu/linux_specific/linux_exceptions.hpp"
#include "ebisu/linux_specific/linux_specific_logging.hpp"
#include "ebisu/utils/exception/make_exception.hpp"
#include "ebisu/utils/streamers/map.hpp"
#include "ebisu/utils/streamers/vector.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>

namespace ebisu {
namespace linux_specific {
/**
 Information stored on a processor basis in cpuinfo.
 The fields in this class are dynamically generated from parsing
 cpuinfo.
*/
class Processor {
 public:
  using Proc_map_t = std::map<std::string, std::string>;

  Processor(int processor, Proc_map_t const& proc_map)
      : processor_(processor), proc_map_(proc_map) {}

  friend inline std::ostream& operator<<(std::ostream& out,
                                         Processor const& item) {
    using ebisu::utils::streamers::operator<<;
    out << "Processor(" << &item << ") {";
    out << "\n  proc_map:" << item.proc_map_;
    out << "\n  processor:" << item.processor_;
    out << "\n}\n";
    return out;
  }

  std::string vendor_id() const {
    auto found = proc_map_.find("vendor_id");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string cpu_family() const {
    auto found = proc_map_.find("cpu_family");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string model() const {
    auto found = proc_map_.find("model");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string model_name() const {
    auto found = proc_map_.find("model_name");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string stepping() const {
    auto found = proc_map_.find("stepping");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string microcode() const {
    auto found = proc_map_.find("microcode");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string cpu_mhz() const {
    auto found = proc_map_.find("cpu_mhz");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string cache_size() const {
    auto found = proc_map_.find("cache_size");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string physical_id() const {
    auto found = proc_map_.find("physical_id");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string siblings() const {
    auto found = proc_map_.find("siblings");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string core_id() const {
    auto found = proc_map_.find("core_id");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string cpu_cores() const {
    auto found = proc_map_.find("cpu_cores");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string apicid() const {
    auto found = proc_map_.find("apicid");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string initial_apicid() const {
    auto found = proc_map_.find("initial_apicid");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string fpu() const {
    auto found = proc_map_.find("fpu");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string fpu_exception() const {
    auto found = proc_map_.find("fpu_exception");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string cpuid_level() const {
    auto found = proc_map_.find("cpuid_level");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string wp() const {
    auto found = proc_map_.find("wp");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string flags() const {
    auto found = proc_map_.find("flags");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string bugs() const {
    auto found = proc_map_.find("bugs");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string bogomips() const {
    auto found = proc_map_.find("bogomips");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string clflush_size() const {
    auto found = proc_map_.find("clflush_size");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string cache_alignment() const {
    auto found = proc_map_.find("cache_alignment");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string address_sizes() const {
    auto found = proc_map_.find("address_sizes");
    return (found != proc_map_.end()) ? found->second : "";
  }

  std::string power_management() const {
    auto found = proc_map_.find("power_management");
    return (found != proc_map_.end()) ? found->second : "";
  }

  //! getter for proc_map_ (access is Ro)
  Proc_map_t const& proc_map() const { return proc_map_; }

  //! getter for processor_ (access is Ro)
  int processor() const { return processor_; }

 private:
  /**
   Map of processors
  */
  Proc_map_t proc_map_{};
  int processor_{};
};

using Processor_list_t = std::vector<Processor>;

/**
 Class to parse cpuinfo file. This might be of use to interrogate
 from code the stats of the machine for better enabling <apple to apple>
 comparisons.

*/
class Cpu_info {
 public:
  Cpu_info(Cpu_info const& other) = delete;

  Cpu_info(Cpu_info&& other) = delete;

  Cpu_info& operator=(Cpu_info const&) = delete;

  Cpu_info& operator=(Cpu_info&&) = delete;

  friend inline std::ostream& operator<<(std::ostream& out,
                                         Cpu_info const& item) {
    using ebisu::utils::streamers::operator<<;
    out << "Cpu_info(" << &item << ") {";
    out << "\n  processors:" << item.processors_;
    out << "\n}\n";
    return out;
  }

  static Cpu_info& instance() {
    static Cpu_info instance_s;
    return instance_s;
  }

  //! getter for processors_ (access is Ro)
  Processor_list_t const& processors() const { return processors_; }

 private:
  // custom <ClsPrivate Cpu_info>

  // end <ClsPrivate Cpu_info>

  Cpu_info() {
    // custom <Cpu_info defaultCtor>

    using namespace std;
    using namespace boost;

    ifstream input{"/proc/cpuinfo"};
    string text{istreambuf_iterator<char>(input), istreambuf_iterator<char>()};

    regex proc_split_re{"processor\\s*:\\s*"};
    regex proc_id_re{"^(\\d+)\\s*"};
    regex entry_split_re{"\\n"};
    regex entry_re{"([\\w\\s]+):\\s*(.+)"};

    sregex_token_iterator outer_i{text.begin(), text.end(), proc_split_re, -1};
    sregex_token_iterator outer_j;
    while (outer_i != outer_j) {
      string entry{(*outer_i++).str()};
      sregex_token_iterator inner_i{entry.begin(), entry.end(), entry_split_re,
                                    -1};
      sregex_token_iterator inner_j;
      smatch what;

      if (inner_i != inner_j) {
        string line{(*inner_i++).str()};
        int proc_id{-1};
        if (regex_match(line, what, proc_id_re)) {
          proc_id = lexical_cast<int>(what[1]);
        } else {
          std::string msg{"Expected proc id in line: "};
          msg += line;
          throw runtime_error(msg);
        }
        assert(proc_id >= 0);

        Processor::Proc_map_t map;

        while (inner_i != inner_j) {
          string line{(*inner_i++).str()};
          if (regex_match(line, what, entry_re)) {
            string key{what[1].str()};
            string value{what[2].str()};
            algorithm::trim(key);
            algorithm::trim(value);
            map[key] = value;
          }
        }

        processors_.emplace_back(proc_id, map);
      }
    }

    // end <Cpu_info defaultCtor>
  }

  /**
   List of processors
  */
  Processor_list_t processors_{};
};

}  // namespace linux_specific
}  // namespace ebisu

#endif  // __EBISU_LINUX_SPECIFIC_CPU_INFO_HPP__
