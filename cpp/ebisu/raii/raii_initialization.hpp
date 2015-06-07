#ifndef __EBISU_RAII_RAII_INITIALIZATION_HPP__
#define __EBISU_RAII_RAII_INITIALIZATION_HPP__

#include "ebisu/raii/api_initializer.hpp"
#include "ebisu/raii/raii_logging.hpp"

namespace ebisu {
namespace raii {
/// Initialization function for raii
inline void raii_init() {
#if defined(LIB_INIT_LOGGING)
  raii_logger->info("init of raii (version 0.0.1)");
#endif
}

/// Uninitialization function for raii
inline void raii_uninit() {
#if defined(LIB_INIT_LOGGING)
  raii_logger->info("uninit of raii (version 0.0.1)");
#endif
}

/// Singleton for raii initializer
inline ebisu::raii::Api_initializer<> raii_initializer_() {
  static ebisu::raii::Api_initializer<> raii_initializer{raii_init,
                                                         raii_uninit};
  return raii_initializer;
};

/// Internal linkage (i.e. 1 per translation unit) initializer for raii
namespace {
ebisu::raii::Api_initializer<> raii_initializer{raii_initializer_()};
}

}  // namespace raii
}  // namespace ebisu

#endif  // __EBISU_RAII_RAII_INITIALIZATION_HPP__
