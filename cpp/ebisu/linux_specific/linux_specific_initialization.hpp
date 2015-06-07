#ifndef __EBISU_LINUX_SPECIFIC_LINUX_SPECIFIC_INITIALIZATION_HPP__
#define __EBISU_LINUX_SPECIFIC_LINUX_SPECIFIC_INITIALIZATION_HPP__

#include "ebisu/linux_specific/linux_specific_logging.hpp"
#include "ebisu/raii/api_initializer.hpp"

namespace ebisu {
namespace linux_specific {
/// Initialization function for linux_specific
inline void linux_specific_init() {
#if defined(LIB_INIT_LOGGING)
  linux_specific_logger->info("init of linux_specific (version 0.0.0)");
#endif
}

/// Uninitialization function for linux_specific
inline void linux_specific_uninit() {
#if defined(LIB_INIT_LOGGING)
  linux_specific_logger->info("uninit of linux_specific (version 0.0.0)");
#endif
}

/// Singleton for linux_specific initializer
inline ebisu::raii::Api_initializer<> linux_specific_initializer_() {
  static ebisu::raii::Api_initializer<> linux_specific_initializer{
      linux_specific_init, linux_specific_uninit};
  return linux_specific_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for
/// linux_specific
namespace {
ebisu::raii::Api_initializer<> linux_specific_initializer{
    linux_specific_initializer_()};
}

}  // namespace linux_specific
}  // namespace ebisu

#endif  // __EBISU_LINUX_SPECIFIC_LINUX_SPECIFIC_INITIALIZATION_HPP__
