#ifndef __FCS_LINUX_SPECIFIC_LINUX_SPECIFIC_INITIALIZATION_HPP__
#define __FCS_LINUX_SPECIFIC_LINUX_SPECIFIC_INITIALIZATION_HPP__

#include "fcs/linux_specific/linux_specific_logging.hpp"
#include "fcs/raii/api_initializer.hpp"

namespace fcs {
namespace linux_specific {
/// Initialization function for linux_specific
inline void linux_specific_init() {
  linux_specific_logger->info("init of linux_specific (version 0.0.0)");
}

/// Uninitialization function for linux_specific
inline void linux_specific_uninit() {
  linux_specific_logger->info("uninit of linux_specific (version 0.0.0)");
}

/// Singleton for linux_specific initializer
inline fcs::raii::Api_initializer<> linux_specific_initializer_() {
  static fcs::raii::Api_initializer<> linux_specific_initializer{
      linux_specific_init, linux_specific_uninit};
  return linux_specific_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for
/// linux_specific
namespace {
fcs::raii::Api_initializer<> linux_specific_initializer{
    linux_specific_initializer_()};
}

}  // namespace linux_specific
}  // namespace fcs

#endif  // __FCS_LINUX_SPECIFIC_LINUX_SPECIFIC_INITIALIZATION_HPP__
